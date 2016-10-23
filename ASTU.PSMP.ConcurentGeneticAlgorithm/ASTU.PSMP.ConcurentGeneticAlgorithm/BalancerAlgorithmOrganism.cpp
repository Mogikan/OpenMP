#include "BalancerAlgorithmOrganism.h"



BalancerAlgorithmOrganism::BalancerAlgorithmOrganism(shared_ptr<TaskList> tasks,int pcCount)
{
	this->tasks = tasks;
	this->pcCount = pcCount;
}

BalancerAlgorithmOrganism::BalancerAlgorithmOrganism(std::list<shared_ptr<PCTaskDescriptorList>> newPCList, shared_ptr<TaskList> taskList, int pcCount)
{
	this->pcList = newPCList;
	this->pcCount = pcCount;
	this->tasks = taskList;
}


BalancerAlgorithmOrganism::~BalancerAlgorithmOrganism()
{
}

void BalancerAlgorithmOrganism::Initialize()
{
	auto allTasks = tasks->GetAllTasks();
	for (int i = 0; i < pcCount; i++)
	{
		pcList.push_back(shared_ptr<PCTaskDescriptorList>(new PCTaskDescriptorList()));
	}
	for (int i = 0; i < allTasks.size(); i++)
	{
		auto pcForTask = rand() % pcCount;
		std::list<shared_ptr<PCTaskDescriptorList>>::iterator it = std::next(pcList.begin(), pcForTask);
		(*it)->AddTask(allTasks[i]);
	}
}

double BalancerAlgorithmOrganism::MeasureFitness()
{
	std::list <shared_ptr<PCTaskDescriptorList>> ::iterator iterator,iteratorCopy;
	std::unordered_map<int,shared_ptr<TaskDescriptor>> countedTasks;
	bool breakIteration = false;
	double maxExecutionTime = -DBL_MAX;
	double penalty = 0;
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
				auto precedingTask = precedingTasks[i];
				int precedingTaskNumber = precedingTask->GetTaskNumber();
				auto foundDescriptorIterator = countedTasks.find(precedingTaskNumber);
				if (foundDescriptorIterator == countedTasks.end())
				{
					if (pc->ContainsTask(precedingTaskNumber)) 
					{
						penalty = 1000;
						iterator++;
						breakIteration = true;
						break;
					}
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
			countedTasks.insert({ taskDescriptor->GetTask()->GetTaskNumber(),taskDescriptor });
			pc->ConsumeTask(startTime);
		}

		maxExecutionTime = max(pc->GetConsumedTime(), maxExecutionTime);
	}
	return maxExecutionTime;
}

shared_ptr<PCTaskDescriptorList> GetTaskPC(int taskNumber, std::list<shared_ptr<PCTaskDescriptorList>> newPCList)
{

	for (auto iterator = newPCList.begin(); iterator != newPCList.end(); ++iterator)
	{
		if ((*iterator)->ContainsTask(taskNumber))
		{
			return (*iterator);
		}
	}
}

shared_ptr<BalancerAlgorithmOrganism> BalancerAlgorithmOrganism::Mutate()
{
	auto newPCList = ClonePCList();
	vector<int> leftMutationTasks;
	for (int i = 0; i < tasks->Size(); i++)
	{
		leftMutationTasks.push_back(i);
	}
	int pairsCount = leftMutationTasks.size()/2;
	for (int i = 0; i < pairsCount; i++)
	{
		//TODO: get from genetic parameters
		if (rand() / RAND_MAX < 0.95)
		{
			continue;
		}
		int taskIndex1 = leftMutationTasks.at(rand() % leftMutationTasks.size());
		int task1 = leftMutationTasks.at(taskIndex1);
		leftMutationTasks.erase(leftMutationTasks.begin() + taskIndex1);

		int taskIndex2 = leftMutationTasks.at(rand() % leftMutationTasks.size());
		int task2 = leftMutationTasks.at(taskIndex2);
		leftMutationTasks.erase(leftMutationTasks.begin() + taskIndex2);

		auto pc1 = GetTaskPC(task1, newPCList);
		auto pc2 = GetTaskPC(task2, newPCList);
		auto firstIndex = pc1->GetTaskIndex(task1);
		auto secondIndex = pc2->GetTaskIndex(task2);
		auto taskDescriptor1 = pc1->GetTaskAtIndex(firstIndex);
		auto taskDescriptor2 = pc2->GetTaskAtIndex(secondIndex);
		pc1->ReplaceTaskDescriptor(firstIndex, taskDescriptor2);
		pc2->ReplaceTaskDescriptor(firstIndex, taskDescriptor1);
	}
	return shared_ptr<BalancerAlgorithmOrganism>(new BalancerAlgorithmOrganism(newPCList, tasks, pcCount));
}

void MarkUsedTasks(std::list<shared_ptr<PCTaskDescriptorList>> taskList, std::vector<bool> usedTasks)
{
	for (auto iterator = taskList.begin(); iterator != taskList.end(); iterator++)
	{
		for (int i = 0; i < (*iterator)->Size(); i++)
		{
			usedTasks[(*iterator)->GetTaskAtIndex(i)->GetTask()->GetTaskNumber()] = true;
		}		
	}
}


void RemoveUsedTasks(std::list<shared_ptr<PCTaskDescriptorList>> taskList, std::vector<bool> usedTasks)
{
	for (auto iterator = taskList.begin(); iterator != taskList.end(); iterator++)
	{
		for (int i = 0; i < (*iterator)->Size(); i++)
		{
			if (usedTasks[(*iterator)->GetTaskAtIndex(i)->GetTask()->GetTaskNumber()])
			{
				(*iterator)->RemoveTaskDescriptorAtIndex(i);
			}
		}
	}
}

void AddLeftTasks(std::list<shared_ptr<PCTaskDescriptorList>> taskList, std::vector<bool> usedTasks, shared_ptr<TaskList> tasks, int listSize)
{
	std::vector<shared_ptr<Task>> allTasks = tasks->GetAllTasks();
	for (int i = 0; i < allTasks.size(); i++)
	{
		if (!usedTasks[i])
		{
			auto task = allTasks[i];
			int destinationIndex = rand() % listSize;
			auto destinationNode = taskList.begin();
			std::next(destinationNode, destinationIndex);
			(*destinationNode)->AddTask(task);
		}
	}
}

std::pair<shared_ptr<BalancerAlgorithmOrganism>, shared_ptr<BalancerAlgorithmOrganism>> BalancerAlgorithmOrganism::ProduceChildren(shared_ptr<BalancerAlgorithmOrganism> parent1, shared_ptr<BalancerAlgorithmOrganism> parent2,shared_ptr<TaskList> tasks, int pcNumber)
{
	int slicePosition = rand() % (pcNumber - 2) + 1;//except 0 and max	
	auto parent1PCList = parent1->ClonePCList();
	auto parent2PCList = parent2->ClonePCList();
	auto genesSlicePosition = std::next(parent1PCList.begin(), slicePosition);	
	std::list<shared_ptr<PCTaskDescriptorList>> child1PartOne(parent1PCList.begin(), genesSlicePosition);
	std::list<shared_ptr<PCTaskDescriptorList>> child1PartTwo(genesSlicePosition,parent1PCList.end());
	std::list<shared_ptr<PCTaskDescriptorList>> child2PartOne(parent2PCList.begin(), genesSlicePosition);
	std::list<shared_ptr<PCTaskDescriptorList>> child2PartTwo(genesSlicePosition, parent2PCList.end());
	std::vector<bool> usedTasksChild1;
	for (int i = 0; i < tasks->Size(); i++)
	{
		usedTasksChild1.push_back(false);
	}
	MarkUsedTasks(child1PartOne, usedTasksChild1);
	RemoveUsedTasks(child2PartTwo, usedTasksChild1);
	MarkUsedTasks(child2PartTwo, usedTasksChild1);
	//TODO: check last argument
	AddLeftTasks(child2PartTwo, usedTasksChild1, tasks,pcNumber - slicePosition);
	child1PartOne.splice(child1PartOne.end(), child2PartTwo);
	auto child1 = shared_ptr<BalancerAlgorithmOrganism>(new BalancerAlgorithmOrganism(child1PartOne, tasks, pcNumber));

	std::vector<bool> usedTasksChild2;
	for (int i = 0; i < tasks->Size(); i++)
	{
		usedTasksChild2.push_back(false);
	}
	MarkUsedTasks(child2PartOne, usedTasksChild2);
	RemoveUsedTasks(child1PartTwo, usedTasksChild2);
	MarkUsedTasks(child1PartTwo, usedTasksChild2);
	//TODO: check last argument
	AddLeftTasks(child1PartTwo, usedTasksChild2, tasks, pcNumber - slicePosition);
	child2PartOne.splice(child2PartOne.end(), child1PartTwo);
	auto child2 = shared_ptr<BalancerAlgorithmOrganism>(new BalancerAlgorithmOrganism(child2PartOne, tasks, pcNumber));
	return std::pair<shared_ptr<BalancerAlgorithmOrganism>, shared_ptr<BalancerAlgorithmOrganism>>(child1,child2);
}

std::list<shared_ptr<PCTaskDescriptorList>> BalancerAlgorithmOrganism::ClonePCList()
{
	auto pcList = std::list<shared_ptr<PCTaskDescriptorList>>();
	for (std::list<shared_ptr<PCTaskDescriptorList>>::iterator iterator = pcList.begin(); iterator != pcList.end(); ++iterator)
	{
		pcList.push_back((*iterator)->Clone());
	}
	return pcList;
}

