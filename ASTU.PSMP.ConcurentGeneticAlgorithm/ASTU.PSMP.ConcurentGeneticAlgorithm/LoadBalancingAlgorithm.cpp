#include "LoadBalancingAlgorithm.h"



LoadBalancingAlgorithm::LoadBalancingAlgorithm(shared_ptr<GeneticAlgorithmParameters> geneticParameters,shared_ptr<TaskList> tasklist):GeneticAlgorithm(geneticParameters)
{
	this->tasks = tasklist;	
}


LoadBalancingAlgorithm::~LoadBalancingAlgorithm()
{
}

shared_ptr<BalancerAlgorithmOrganism> LoadBalancingAlgorithm::CreateOrganism()
{
	auto result = shared_ptr<BalancerAlgorithmOrganism>(new BalancerAlgorithmOrganism(this->tasks, GeneticAlgorithmParameters::PCCount));
	result->Initialize();
	return result;
}

std::pair<shared_ptr<BalancerAlgorithmOrganism>, shared_ptr<BalancerAlgorithmOrganism>> LoadBalancingAlgorithm::ProduceChildren(shared_ptr<BalancerAlgorithmOrganism> parent1, shared_ptr<BalancerAlgorithmOrganism> parent2)
{
	return BalancerAlgorithmOrganism::ProduceChildren(parent1, parent2, this->tasks, GeneticAlgorithmParameters::PCCount);
}

shared_ptr<BalancerAlgorithmOrganism> LoadBalancingAlgorithm::ProduceMutant(shared_ptr<BalancerAlgorithmOrganism> organism)
{
	return organism->Mutate();
}

double LoadBalancingAlgorithm::MeasureFitness(shared_ptr<BalancerAlgorithmOrganism> organism)
{
	return organism->MeasureFitness();
}
