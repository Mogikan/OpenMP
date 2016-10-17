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
	BalancerAlgorithmOrganism();
	~BalancerAlgorithmOrganism();
private:
	std::list<PCTaskDescriptorList*> pcList;

	// Inherited via Organism
	BalancerAlgorithmOrganism*  CreateOrganism();
	virtual double MeasureFitness();
};

