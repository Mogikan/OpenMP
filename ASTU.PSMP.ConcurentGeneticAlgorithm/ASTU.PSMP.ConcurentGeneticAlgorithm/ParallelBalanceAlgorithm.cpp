#include "ParallelBalanceAlgorithm.h"

ParallelBalanceAlgorithm::ParallelBalanceAlgorithm(shared_ptr<GeneticAlgorithmParameters> geneticParameters, shared_ptr<TaskList> tasklist,int islandsCount,int migrationCount)
{
	this->geneticParameters = geneticParameters;
	this->tasklist = tasklist;
	this->islandsCount = islandsCount;
	this->migrationCount = migrationCount;
}

ParallelBalanceAlgorithm::~ParallelBalanceAlgorithm()
{
}

void ParallelBalanceAlgorithm::Execute()
{
	int islandPopulation = geneticParameters->GetInitialPopulationSize() / islandsCount;
	int islandReproductionNumber = geneticParameters->GetReproductionNumber() / islandsCount;
	int islandGenerationCount = geneticParameters->GetGenerationCount() / migrationCount;
	shared_ptr<GeneticAlgorithmParameters> islandGeneticParameters(new GeneticAlgorithmParameters(*geneticParameters.get()));
	islandGeneticParameters->SetInitialPopulationSize(islandPopulation);
	islandGeneticParameters->SetReproductionNumber(islandReproductionNumber);
	islandGeneticParameters->SetGenerationCount(islandGenerationCount);
	for (int i = 0; i < islandPopulation; i++)
	{
		shared_ptr<LoadBalancingAlgorithm> loadBalancingAlgorithm(new LoadBalancingAlgorithm(islandGeneticParameters, tasklist));
		this->islands.push_back(loadBalancingAlgorithm);
	}
	//TODO: Move to separate method
	for (int i = 0; i < migrationCount; i++)
	{
		shared_ptr<BalancerAlgorithmOrganism> bestOrganism;
		int bestIndex = 0;
		for (auto iterator = islands.begin(); iterator != islands.end(); iterator++)
		{
			(*iterator)->Execute();
			auto islandBestOrganism = (*iterator)->SelectBest();
			if (bestOrganism == nullptr)
			{
				bestIndex = iterator - islands.begin();
				bestOrganism = islandBestOrganism;
			}
			else
			{
				bestIndex = iterator - islands.begin();
				bestOrganism = islandBestOrganism;
				bestOrganism = (bestOrganism->MeasureFitness() < islandBestOrganism->MeasureFitness()) ? islandBestOrganism : bestOrganism;
			}
		}
		for (auto iterator = islands.begin(); iterator != islands.end(); iterator++)
		{
			if (iterator - islands.begin() != bestIndex)
			{
				(*iterator)->ReplaceWorst(bestOrganism);
			}
		}
	}
}
