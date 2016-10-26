#pragma once
#include "Organism.h"
#include <list>
#include <unordered_map>
#include "Task.h"
#include "TaskList.h"
#include "PCTaskDescriptorList.h"
#include <memory>
#include <Windows.h>
#include "GeneticAlgorithmParameters.h"
using namespace std;
class BalancerAlgorithmOrganism
	
{
public:
	BalancerAlgorithmOrganism(shared_ptr<TaskList> tasks,int pcCount);
	BalancerAlgorithmOrganism(std::list<shared_ptr<PCTaskDescriptorList>> newPCList, shared_ptr<TaskList> taskList, int pcCount);
	~BalancerAlgorithmOrganism();
	virtual double MeasureFitness();
	void Initialize();
	shared_ptr<BalancerAlgorithmOrganism> Mutate();
	static std::pair<shared_ptr<BalancerAlgorithmOrganism>, shared_ptr<BalancerAlgorithmOrganism>> ProduceChildren(shared_ptr<BalancerAlgorithmOrganism> parent1, shared_ptr<BalancerAlgorithmOrganism> parent2, shared_ptr<TaskList> tasks, int pcNumber);
private:
	std::list<shared_ptr<PCTaskDescriptorList>> pcList;
	shared_ptr<TaskList> tasks;
	int pcCount;		
	std::list<shared_ptr<PCTaskDescriptorList>> ClonePCList();

};

