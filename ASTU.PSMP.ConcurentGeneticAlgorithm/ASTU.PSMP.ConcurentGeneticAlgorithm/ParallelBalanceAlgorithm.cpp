#include "ParallelBalanceAlgorithm.h"

ParallelBalanceAlgorithm::ParallelBalanceAlgorithm(GeneticAlgorithmParameters * geneticParameters, TaskList * tasklist,int islandsCount,int migrationCount)
{
	this->geneticParameters = geneticParameters;
	this->tasklist = tasklist;
	int islandPopulation = geneticParameters->GetInitialPopulationSize() / islandsCount;
	int islandReproductionNumber = geneticParameters->GetReproductionNumber() / islandsCount;
	int islandGenerationCount = geneticParameters->GetGenerationCount()/migrationCount;
	auto islandGeneticParameters = new GeneticAlgorithmParameters(*geneticParameters);
	islandGeneticParameters->SetInitialPopulationSize(islandPopulation);
	islandGeneticParameters->SetReproductionNumber(islandReproductionNumber);
	islandGeneticParameters->SetGenerationCount(islandGenerationCount);
	for (int i = 0; i < islandPopulation; i++)
	{
		auto loadBalancingAlgorithm = new LoadBalancingAlgorithm(islandGeneticParameters,tasklist);
		this->islands.push_back(loadBalancingAlgorithm);
	}
	//TODO: Move to separate method
	for (int i = 0; i < migrationCount; i++)
	{
		BalancerAlgorithmOrganism* bestOrganism = nullptr;
		int bestIndex=0;
		for (auto iterator=islands.begin();iterator!=islands.end();iterator++)
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

ParallelBalanceAlgorithm::~ParallelBalanceAlgorithm()
{
}
