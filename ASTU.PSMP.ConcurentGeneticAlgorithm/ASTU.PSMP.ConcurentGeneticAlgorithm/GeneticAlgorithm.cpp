#include "GeneticAlgorithm.h"
#include <set>
#include <iostream>
using namespace std;


GeneticAlgorithm::GeneticAlgorithm(shared_ptr<GeneticAlgorithmParameters> geneticParameters)
{
	this->geneticParameters = geneticParameters;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

shared_ptr<BalancerAlgorithmOrganism> GeneticAlgorithm::SelectBest()
{	
	shared_ptr<BalancerAlgorithmOrganism> result (*std::min_element(population.begin(), population.end(), [](shared_ptr<BalancerAlgorithmOrganism> a, shared_ptr<BalancerAlgorithmOrganism> b)->double { return a->MeasureFitness() < b->MeasureFitness(); }));
	return result;
}

int GeneticAlgorithm::GetWorstIndex()
{
	return std::max_element(population.begin(), population.end(), [](shared_ptr<BalancerAlgorithmOrganism> a, shared_ptr<BalancerAlgorithmOrganism> b)->double { return a->MeasureFitness() < b->MeasureFitness(); }) - population.begin();
}


void GeneticAlgorithm::ReplaceWorst(shared_ptr<BalancerAlgorithmOrganism> organism)
{
	population[GetWorstIndex()] = organism;

}

void GeneticAlgorithm::WriteToDebugOutput(string s)
{
	std::ostringstream os_;
	os_ << s;
	OutputDebugString(os_.str().c_str());
}

string GeneticAlgorithm::ToString(double value)
{
	std::ostringstream strs;
	strs << value << "\n\r";
	std::string str = strs.str();
	return str;
}

void GeneticAlgorithm::Execute()
{
	InitPopulation();
	for (int i = 0; i < geneticParameters->GetGenerationCount(); i++)
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
		auto parent1Organism = population[notUsedOrganisms[parent1Index]];
		notUsedOrganisms.erase(notUsedOrganisms.begin() + parent1Index);
		int parent2Index = rand() % notUsedOrganisms.size();
		auto parent2Organism = population[notUsedOrganisms[parent2Index]];
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
		if (((double)rand()) / RAND_MAX < geneticParameters->GetMutationProbability()) 
		{
			auto originalOrganism = population[i];
			auto mutantOrganism = ProduceMutant(originalOrganism);
			shared_ptr<BalancerAlgorithmOrganism> leftOrganism;
			if (((double)rand()) / RAND_MAX < geneticParameters->GetGoodOrganizmSurvivalProbability())
			{
				leftOrganism = MeasureFitness(mutantOrganism) < MeasureFitness(originalOrganism) ? mutantOrganism : originalOrganism;
			}
			else 
			{
				leftOrganism = MeasureFitness(mutantOrganism) < MeasureFitness(originalOrganism) ? originalOrganism : mutantOrganism;
			}
			//WriteToDebugOutput(ToString(mutantOrganism->MeasureFitness()));
			//WriteToDebugOutput(ToString(originalOrganism->MeasureFitness()));
			//WriteToDebugOutput("left");
			//WriteToDebugOutput(ToString(leftOrganism->MeasureFitness()));
			population[i] = leftOrganism;
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
	for (int i = 0; i < population.size(); i++)
	{
		notFightedYet.push_back(i);
	}
	std::set<int,inverseOrderStruct> diedOrganisms;
	for (int i = 0; i < geneticParameters->GetReproductionNumber()*2; i++)
	{
		int randomFighterIndex1 = rand() % notFightedYet.size();
		int fighterIndex1 = notFightedYet.at(randomFighterIndex1);
		notFightedYet.erase(notFightedYet.begin() + randomFighterIndex1);
		int randomFighterIndex2 = rand() % notFightedYet.size();
		int fighterIndex2 = notFightedYet.at(randomFighterIndex2);
		notFightedYet.erase(notFightedYet.begin() + randomFighterIndex2);
		int deathIndex;
		if (((double)rand()) / RAND_MAX < geneticParameters->GetBadOrganizmDeathProbability()) 		
		{
			deathIndex = (MeasureFitness(population[fighterIndex1]) > MeasureFitness(population[fighterIndex2])) ? fighterIndex1 : fighterIndex2;
		}
		else 
		{
			deathIndex = (MeasureFitness(population[fighterIndex1]) > MeasureFitness(population[fighterIndex2])) ? fighterIndex2 : fighterIndex1;
		}

		//WriteToDebugOutput(ToString(population[fighterIndex1]->MeasureFitness()));		
		//WriteToDebugOutput(ToString(population[fighterIndex2]->MeasureFitness()));
		//WriteToDebugOutput("Death");
		//WriteToDebugOutput(ToString(population[deathIndex]->MeasureFitness()));
		diedOrganisms.insert(deathIndex);
	}
	while (!diedOrganisms.empty()) {
		population.erase(population.begin()+ *diedOrganisms.begin());
		diedOrganisms.erase(diedOrganisms.begin());
	}
	
}
