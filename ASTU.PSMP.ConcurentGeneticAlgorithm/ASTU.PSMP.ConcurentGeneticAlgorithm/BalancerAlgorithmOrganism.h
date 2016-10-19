#pragma once
#include "Organism.h"
#include <list>
#include <unordered_map>
#include "Task.h"
#include "TaskList.h"
#include "PCTaskDescriptorList.h"

using namespace std;
class BalancerAlgorithmOrganism
	
{
public:
	BalancerAlgorithmOrganism(TaskList* tasks,int pcCount);
	BalancerAlgorithmOrganism(std::list<PCTaskDescriptorList*> newPCList, TaskList* taskList, int pcCount);
	~BalancerAlgorithmOrganism();
	virtual double MeasureFitness();
	BalancerAlgorithmOrganism* CreateOrganism();
	BalancerAlgorithmOrganism* Mutate();

private:
	std::list<PCTaskDescriptorList*> pcList;
	TaskList* tasks;
	int pcCount;		
	std::list<PCTaskDescriptorList*> ClonePCList();

};

