#include "BalancerAlgorithmOrganism.h"



BalancerAlgorithmOrganism::BalancerAlgorithmOrganism(TaskList * tasks,int pcCount)
{
	this->tasks = tasks;
	this->pcCount = pcCount;
}

BalancerAlgorithmOrganism::~BalancerAlgorithmOrganism()
{
}

BalancerAlgorithmOrganism * BalancerAlgorithmOrganism::CreateOrganism()
{
	auto allTasks = tasks->GetAllTasks();
	for (int i = 0; i < pcCount; i++)
	{
		pcList.push_back(new PCTaskDescriptorList());
	}
	for (int i = 0; i < allTasks.size(); i++)
	{
		auto pcForTask = rand() % pcCount;
		std::list<PCTaskDescriptorList*>::iterator it = std::next(pcList.begin(), pcForTask);
		(*it)->AddTask(allTasks.at(i));
	}
	return this;
}

double BalancerAlgorithmOrganism::MeasureFitness()
{
	std::list < PCTaskDescriptorList* > ::iterator iterator,iteratorCopy;
	std::unordered_map<int,TaskDescriptor*> countedTasks;
	bool breakIteration = false;
	double maxExecutionTime = -DBL_MAX;
	for (iterator = pcList.begin(); iterator != pcList.end(); (breakIteration)?iterator:iterator++)
	{
		auto pc = (*iterator);
		breakIteration = false;			
		while (pc->HasNotConsumedTask())
		{
			auto taskDescriptor = pc->GetCurrentTask();
			auto precedingTasks = taskDescriptor->GetTask()->GetPrecedingTasks();
			double startTime = pc->GetConsumedTime();
			for (int i = 0; i < precedingTasks.size(); i++)
			{
				auto precedingTask = precedingTasks.at(i);
				int precedingTaskNumber = precedingTask->GetTaskNumber();
				auto foundDescriptorIterator = countedTasks.find(precedingTaskNumber);
				if (foundDescriptorIterator == countedTasks.end())
				{
					iteratorCopy = iterator;
					if (iterator == pcList.begin()) 
					{
						iteratorCopy++;
					}
					else
					{
						iteratorCopy--;
					}
					pcList.splice(pcList.end(), pcList, iterator);
					iterator = iteratorCopy;
					iteratorCopy++;
					breakIteration = true;
					break;
				}
				else 
				{
					startTime = std::max(startTime,foundDescriptorIterator->second->GetFinishTime());
				}
			}
			if (breakIteration)
			{
				break;
			}
			pc->ConsumeTask(startTime);
		}

		maxExecutionTime = max(pc->GetConsumedTime(), maxExecutionTime);
	}
	return maxExecutionTime;
}
