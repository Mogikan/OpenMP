#include "LoadBalancingAlgorithm.h"



LoadBalancingAlgorithm::LoadBalancingAlgorithm(GeneticAlgorithmParameters* geneticParameters,TaskList* tasklist):GeneticAlgorithm(geneticParameters)
{
	this->geneticParameters = geneticParameters;
	this->tasks = tasklist;
}


LoadBalancingAlgorithm::~LoadBalancingAlgorithm()
{
}

BalancerAlgorithmOrganism * LoadBalancingAlgorithm::CreateOrganism()
{
	return new BalancerAlgorithmOrganism(this->tasks,this->PCCount);
}

std::pair<BalancerAlgorithmOrganism*, BalancerAlgorithmOrganism*> LoadBalancingAlgorithm::ProduceChildren(BalancerAlgorithmOrganism * parent1, BalancerAlgorithmOrganism * parent2)
{
	return std::pair<BalancerAlgorithmOrganism*, BalancerAlgorithmOrganism*>();
}

BalancerAlgorithmOrganism * LoadBalancingAlgorithm::ProduceMutant(BalancerAlgorithmOrganism * organism)
{
	return organism->Mutate();
}

double LoadBalancingAlgorithm::MeasureFitness(BalancerAlgorithmOrganism * organism)
{
	return organism->MeasureFitness();
}
