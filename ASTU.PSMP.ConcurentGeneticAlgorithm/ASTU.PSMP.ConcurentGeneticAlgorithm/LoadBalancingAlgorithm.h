#pragma once
#include "GeneticAlgorithm.h"
#include "TaskList.h"
#include "BalancerAlgorithmOrganism.h"
class LoadBalancingAlgorithm :
	public GeneticAlgorithm
{
public:
	LoadBalancingAlgorithm(GeneticAlgorithmParameters * geneticParameters, TaskList* tasklist);
	~LoadBalancingAlgorithm();

	// Inherited via GeneticAlgorithm
	virtual BalancerAlgorithmOrganism * CreateOrganism() override;
	virtual std::pair<BalancerAlgorithmOrganism*, BalancerAlgorithmOrganism*> ProduceChildren(BalancerAlgorithmOrganism * parent1, BalancerAlgorithmOrganism * parent2) override;
	virtual BalancerAlgorithmOrganism * ProduceMutant(BalancerAlgorithmOrganism * organism) override;
	virtual double MeasureFitness(BalancerAlgorithmOrganism * organism) override;
private:
	const int PCCount = 5;
	GeneticAlgorithmParameters* geneticParameters;
	TaskList* tasks;
};

