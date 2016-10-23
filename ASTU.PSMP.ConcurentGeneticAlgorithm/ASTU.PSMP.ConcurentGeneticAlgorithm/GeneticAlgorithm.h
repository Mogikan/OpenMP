#pragma once
#include <vector>
#include <memory>
#include "BalancerAlgorithmOrganism.h"
#include "GeneticAlgorithmParameters.h"

class GeneticAlgorithm
{
public:	
	GeneticAlgorithm(shared_ptr<GeneticAlgorithmParameters> geneticParameters);	
	~GeneticAlgorithm();
	shared_ptr<BalancerAlgorithmOrganism> SelectBest();
	int GetWorstIndex();
	void ReplaceWorst(shared_ptr<BalancerAlgorithmOrganism> organism);
	void Execute();
private:
	std::vector<shared_ptr<BalancerAlgorithmOrganism>> population;
	void InitPopulation();
	void ExecuteStep();
	void ProduceChildren();
	void Mutate();
	void NaturalSelect();	
	virtual shared_ptr<BalancerAlgorithmOrganism> CreateOrganism() = 0;
	virtual std::pair<shared_ptr<BalancerAlgorithmOrganism>, shared_ptr<BalancerAlgorithmOrganism>> ProduceChildren(shared_ptr<BalancerAlgorithmOrganism> parent1, shared_ptr<BalancerAlgorithmOrganism> parent2) = 0;
	virtual shared_ptr<BalancerAlgorithmOrganism> ProduceMutant(shared_ptr<BalancerAlgorithmOrganism> organism) = 0;
	virtual double MeasureFitness(shared_ptr<BalancerAlgorithmOrganism> organism) = 0;
	shared_ptr<GeneticAlgorithmParameters> geneticParameters;
};

