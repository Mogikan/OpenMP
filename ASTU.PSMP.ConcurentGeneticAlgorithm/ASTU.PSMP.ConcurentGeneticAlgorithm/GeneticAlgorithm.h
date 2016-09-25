#pragma once
#include <vector>
#include "Organism.h"
#include "GeneticAlgorithmParameters.h"
class GeneticAlgorithm
{
public:	
	GeneticAlgorithm(GeneticAlgorithmParameters* geneticParameters);	
	~GeneticAlgorithm();
	void Execute(GeneticAlgorithmParameters* geneticAlgorithmParameters);
private:
	std::vector<Organism *> population;
	void InitPopulation();
	void ExecuteStep();
	void ProduceChildren();
	void Mutate();
	void NaturalSelect();
	virtual Organism* CreateOrganism() = 0;
	virtual std::pair<Organism*, Organism*> ProduceChildren(Organism* parent1, Organism* parent2) = 0;
	virtual Organism* ProduceMutant(Organism* organism) = 0;
	virtual double MeasureFitness(Organism* organism) = 0;
	GeneticAlgorithmParameters* geneticParameters;
};

