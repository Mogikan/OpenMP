#include "LoadBalancingAlgorithm.h"



LoadBalancingAlgorithm::LoadBalancingAlgorithm(GeneticAlgorithmParameters* geneticParameters):GeneticAlgorithm(geneticParameters)
{
	
}


LoadBalancingAlgorithm::~LoadBalancingAlgorithm()
{
}

Organism * LoadBalancingAlgorithm::CreateOrganism()
{
	return nullptr;
}

std::pair<Organism*, Organism*> LoadBalancingAlgorithm::ProduceChildren(Organism * parent1, Organism * parent2)
{
	return std::pair<Organism*, Organism*>();
}

Organism * LoadBalancingAlgorithm::ProduceMutant(Organism * organism)
{
	return nullptr;
}

double LoadBalancingAlgorithm::MeasureFitness(Organism * organism)
{
	return 0.0;
}
