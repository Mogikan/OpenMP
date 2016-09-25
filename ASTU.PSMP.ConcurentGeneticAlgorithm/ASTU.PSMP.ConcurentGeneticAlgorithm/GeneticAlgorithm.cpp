#include "GeneticAlgorithm.h"
#include <set>
using namespace std;


GeneticAlgorithm::GeneticAlgorithm(GeneticAlgorithmParameters * geneticParameters)
{
	this->geneticParameters = geneticParameters;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::Execute(GeneticAlgorithmParameters* geneticAlgorithmParameters)
{
	InitPopulation();
	for (int i = 0; i < geneticAlgorithmParameters->GetGenerationCount(); i++)
	{
		ExecuteStep();
	}
}

void GeneticAlgorithm::InitPopulation()
{
	for (int i = 0; i < geneticParameters->GetInitialPopulationSize(); i++)
	{
		population.push_back(CreateOrganism());
	}
}

void GeneticAlgorithm::ExecuteStep()
{
	ProduceChildren();
	Mutate();
	NaturalSelect();
}

void GeneticAlgorithm::ProduceChildren()
{
	std::vector<int> notUsedOrganisms;
	for (int i = 0; i < geneticParameters->GetInitialPopulationSize(); i++)
	{
		notUsedOrganisms.push_back(i);
	}
	for (int j = 0; j < geneticParameters->GetReproductionNumber(); j++)
	{

		int parent1Index = rand() % notUsedOrganisms.size();
		Organism* parent1Organism = population.at(notUsedOrganisms.at(parent1Index));
		notUsedOrganisms.erase(notUsedOrganisms.begin() + parent1Index);
		int parent2Index = rand() % notUsedOrganisms.size();
		Organism* parent2Organism = population.at(notUsedOrganisms.at(parent2Index));
		notUsedOrganisms.erase(notUsedOrganisms.begin() + parent2Index);
		auto children = ProduceChildren(parent1Organism, parent2Organism);
		population.push_back(children.first);
		population.push_back(children.second);
	}
}

void GeneticAlgorithm::Mutate()
{
	for (int i = 0; i < population.size(); i++)
	{
		if (rand() / RAND_MAX < geneticParameters->GetMutationProbability) 
		{
			auto originalOrganism = population.at(i);
			auto mutantOrganism = ProduceMutant(originalOrganism);
			Organism* leftOrganism;
			if (rand() / RAND_MAX < geneticParameters->GetGoodOrganizmSurvivalProbability())
			{
				leftOrganism = MeasureFitness(mutantOrganism) > MeasureFitness(originalOrganism) ? mutantOrganism : originalOrganism;
			}
			else 
			{
				leftOrganism = MeasureFitness(mutantOrganism) > MeasureFitness(originalOrganism) ? originalOrganism : mutantOrganism;
			}
		}
	}
}

struct inverseOrderStruct {
	bool operator() (int const & lhs, int const & rhs) const
	{
		return lhs > rhs;
	}
};

void GeneticAlgorithm::NaturalSelect()
{
	std::vector<int> notFightedYet;
	
	std::set<int,inverseOrderStruct> diedOrganism;
	for (int i = 0; i < geneticParameters->GetReproductionNumber()*2; i++)
	{

	}
}
