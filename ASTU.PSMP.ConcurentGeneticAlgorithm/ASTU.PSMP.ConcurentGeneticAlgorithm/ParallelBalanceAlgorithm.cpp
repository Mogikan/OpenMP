#include "ParallelBalanceAlgorithm.h"
#include <omp.h>
#include <iostream>

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
	for (int i = 0; i < migrationCount; i++)
	{
		shared_ptr<BalancerAlgorithmOrganism> bestOrganism;
		int bestIndex = 0;
		#pragma omp parallel for num_threads(4)
		for (int j = 0;j<islands.size();j++)
		{
			auto island = islands[j];
			island->Execute();
			auto islandBestOrganism = island->SelectBest();
			cout << "island best organizm " << islandBestOrganism->MeasureFitness() << "\n\r";			
			if (bestOrganism == nullptr)
			{				
				bestIndex = j;
				bestOrganism = islandBestOrganism;
			}
			else
			{			
				if (bestOrganism->MeasureFitness() > islandBestOrganism->MeasureFitness())
				{
					bestIndex = j;
					bestOrganism = islandBestOrganism;
				}				 
			}
		}
		
		cout << bestOrganism->MeasureFitness() << "\n\r";
		
		for (auto iterator = islands.begin(); iterator != islands.end(); iterator++)
		{
			if (iterator - islands.begin() != bestIndex)
			{
				(*iterator)->ReplaceWorst(bestOrganism);
			}
		}
	}
}
