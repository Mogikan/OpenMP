#pragma once
#include "GeneticAlgorithm.h"
class LoadBalancingAlgorithm :
	public GeneticAlgorithm
{
public:
	LoadBalancingAlgorithm(GeneticAlgorithmParameters * geneticParameters);
	~LoadBalancingAlgorithm();

	// Inherited via GeneticAlgorithm
	virtual Organism * CreateOrganism() override;
	virtual std::pair<Organism*, Organism*> ProduceChildren(Organism * parent1, Organism * parent2) override;
	virtual Organism * ProduceMutant(Organism * organism) override;
	virtual double MeasureFitness(Organism * organism) override;
};

