#pragma once
#include <vector>
#include "BalancerAlgorithmOrganism.h"
#include "GeneticAlgorithmParameters.h"

class GeneticAlgorithm
{
public:	
	GeneticAlgorithm(GeneticAlgorithmParameters* geneticParameters);	
	~GeneticAlgorithm();
	BalancerAlgorithmOrganism* SelectBest();
	int GetWorstIndex();
	void ReplaceWorst(BalancerAlgorithmOrganism* organism);
	void Execute();
private:
	std::vector<BalancerAlgorithmOrganism *> population;
	void InitPopulation();
	void ExecuteStep();
	void ProduceChildren();
	void Mutate();
	void NaturalSelect();	
	virtual BalancerAlgorithmOrganism* CreateOrganism() = 0;
	virtual std::pair<BalancerAlgorithmOrganism*, BalancerAlgorithmOrganism*> ProduceChildren(BalancerAlgorithmOrganism* parent1, BalancerAlgorithmOrganism* parent2) = 0;
	virtual BalancerAlgorithmOrganism* ProduceMutant(BalancerAlgorithmOrganism* organism) = 0;
	virtual double MeasureFitness(BalancerAlgorithmOrganism* organism) = 0;
	GeneticAlgorithmParameters* geneticParameters;
};

