#pragma once
#include "GeneticAlgorithm.h"
#include "TaskList.h"
#include "BalancerAlgorithmOrganism.h"
class LoadBalancingAlgorithm :
	public GeneticAlgorithm
{
public:
	LoadBalancingAlgorithm(shared_ptr<GeneticAlgorithmParameters> geneticParameters, shared_ptr<TaskList> tasklist);
	~LoadBalancingAlgorithm();

	// Inherited via GeneticAlgorithm
	virtual shared_ptr<BalancerAlgorithmOrganism> CreateOrganism() override;
	virtual std::pair<shared_ptr<BalancerAlgorithmOrganism>, shared_ptr<BalancerAlgorithmOrganism>> ProduceChildren(shared_ptr<BalancerAlgorithmOrganism> parent1, shared_ptr<BalancerAlgorithmOrganism>  parent2) override;
	virtual shared_ptr<BalancerAlgorithmOrganism> ProduceMutant(shared_ptr<BalancerAlgorithmOrganism> organism) override;
	virtual double MeasureFitness(shared_ptr<BalancerAlgorithmOrganism> organism) override;
private:	
	unique_ptr<GeneticAlgorithmParameters> geneticParameters;
	shared_ptr<TaskList> tasks;
};

