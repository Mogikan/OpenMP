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

void WriteToDebugOutput(string s)
{                             
   //std::ostringstream os_;    
   //os_ << s;                   
   //OutputDebugString( os_.str().c_str() );
}

string ToString(double value)
{
	std::ostringstream strs;
	strs << value;
	std::string str = strs.str();
	return str;
}


bool FindDeadLock(shared_ptr<Task> task, std::list <shared_ptr<PCTaskDescriptorList>> pcList,std::unordered_map<int, shared_ptr<TaskDescriptor>> countedTasks, shared_ptr<PCTaskDescriptorList> currentPC)
{
	auto precedingTasks = task->GetPrecedingTasks();
	for (int i = 0; i < precedingTasks.size(); i++)
	{
		auto precedingTaskNumber = precedingTasks[i]->GetTaskNumber();
		if (currentPC->ContainsTask(precedingTaskNumber) && countedTasks.find(precedingTaskNumber) == countedTasks.end())
		{
			return true;
		}
		//auto precedingDescriptor = FindDescriptor(pcList,precedingTaskNumber);
		
		if (FindDeadLock(precedingTasks[i], pcList, countedTasks, currentPC))
		{
			return true;
		}
	}
	return false;
}

double BalancerAlgorithmOrganism::MeasureFitness()
{
	std::list <shared_ptr<PCTaskDescriptorList>> ::iterator iterator,iteratorCopy;
	std::unordered_map<int,shared_ptr<TaskDescriptor>> countedTasks;
	bool breakIteration = false;
	double maxExecutionTime = -DBL_MAX;
	double penalty = 0;
	for (iterator = pcList.begin(); iterator != pcList.end(); iterator++)
	{	
		auto pc = (*iterator);
		for (int i = 0; i < pc->Size(); i++)
		{
			WriteToDebugOutput(" ");
			WriteToDebugOutput(ToString(pc->GetTaskAtIndex(i)->GetTask()->GetTaskNumber()));
		}
		WriteToDebugOutput("\n\r");
	}
	for (iterator = pcList.begin(); iterator != pcList.end(); (breakIteration)?iterator:iterator++)
	{
		auto pc = (*iterator);
		breakIteration = false;			
		while (pc->HasNotConsumedTask())
		{
			auto taskDescriptor = pc->GetCurrentTask();
			if (FindDeadLock(taskDescriptor->GetTask(),pcList,countedTasks,pc))
			{
				return INT32_MAX;// 000;
				//penalty += 1000;
				//iterator++;
				//breakIteration = true;
				//break;
			}
			auto precedingTasks = taskDescriptor->GetTask()->GetPrecedingTasks();
			double startTime = pc->GetConsumedTime();
			for (int i = 0; i < precedingTasks.size(); i++)
			{
				auto precedingTask = precedingTasks[i];
				int precedingTaskNumber = precedingTask->GetTaskNumber();
				auto foundDescriptorIterator = countedTasks.find(precedingTaskNumber);
				if (foundDescriptorIterator == countedTasks.end())
				{
					
					iteratorCopy = iterator;
					bool needIncrement = false;
					if (iterator == pcList.begin()) 
					{
						iteratorCopy++;
					}
					else
					{
						iteratorCopy--;
						needIncrement = true;
					}
					pcList.splice(pcList.end(), pcList, iterator);
					iterator = iteratorCopy;
					if (needIncrement)
					{
						iterator++;
					}
					breakIteration = true;
					break;
				}
				else 
				{
					startTime = max(startTime,foundDescriptorIterator->second->GetFinishTime());
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
	return maxExecutionTime + penalty;
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
		int taskIndex1 = rand() % leftMutationTasks.size();
		int task1 = leftMutationTasks[taskIndex1];
		leftMutationTasks.erase(leftMutationTasks.begin() + taskIndex1);

		int taskIndex2 = rand() % leftMutationTasks.size();
		int task2 = leftMutationTasks[taskIndex2];
		leftMutationTasks.erase(leftMutationTasks.begin() + taskIndex2);

		if (((double)rand()) / INT_MAX > GeneticAlgorithmParameters::PairPermutationProbability)
		{
			continue;
		}

		auto pc1 = GetTaskPC(task1, newPCList);
		auto pc2 = GetTaskPC(task2, newPCList);
		auto firstIndex = pc1->GetTaskIndex(task1);
		auto secondIndex = pc2->GetTaskIndex(task2);
		auto taskDescriptor1 = pc1->GetTaskAtIndex(firstIndex);
		auto taskDescriptor2 = pc2->GetTaskAtIndex(secondIndex);
		pc1->ReplaceTaskDescriptor(firstIndex, taskDescriptor2);
		pc2->ReplaceTaskDescriptor(secondIndex, taskDescriptor1);
	}
	return shared_ptr<BalancerAlgorithmOrganism>(new BalancerAlgorithmOrganism(newPCList, tasks, pcCount));
}

void MarkUsedTasks(std::list<shared_ptr<PCTaskDescriptorList>> taskList, std::vector<bool> & usedTasks)
{
	for (auto iterator = taskList.begin(); iterator != taskList.end(); iterator++)
	{
		for (int i = 0; i < (*iterator)->Size(); i++)
		{
			usedTasks[(*iterator)->GetTaskAtIndex(i)->GetTask()->GetTaskNumber()] = true;
		}		
	}
}


void RemoveUsedTasks(std::list<shared_ptr<PCTaskDescriptorList>> taskList, std::vector<bool> & usedTasks)
{
	for (auto iterator = taskList.begin(); iterator != taskList.end(); iterator++)
	{
		for (int i = 0; i < (*iterator)->Size(); i++)
		{
			if (usedTasks[(*iterator)->GetTaskAtIndex(i)->GetTask()->GetTaskNumber()])
			{
				(*iterator)->RemoveTaskDescriptorAtIndex(i);
				i--;
			}
		}
	}
}

void AddLeftTasks(std::list<shared_ptr<PCTaskDescriptorList>> taskList, std::vector<bool> & usedTasks, shared_ptr<TaskList> & tasks, int listSize)
{
	std::vector<shared_ptr<Task>> allTasks = tasks->GetAllTasks();
	for (int i = 0; i < allTasks.size(); i++)
	{
		if (!usedTasks[i])
		{
			usedTasks[i] = true;
			auto task = allTasks[i];
			int destinationIndex = rand() % listSize;
			auto destinationNode = std::next(taskList.begin(), destinationIndex);
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
	auto genesSlicePosition2 = std::next(parent2PCList.begin(), slicePosition);
	std::list<shared_ptr<PCTaskDescriptorList>> child2PartOne(parent2PCList.begin(), genesSlicePosition2);
	std::list<shared_ptr<PCTaskDescriptorList>> child2PartTwo(genesSlicePosition2, parent2PCList.end());
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
	auto result = std::list<shared_ptr<PCTaskDescriptorList>>();
	for (std::list<shared_ptr<PCTaskDescriptorList>>::iterator iterator = pcList.begin(); iterator != pcList.end(); ++iterator)
	{
		result.push_back((*iterator)->Clone());
	}
	return result;
}

