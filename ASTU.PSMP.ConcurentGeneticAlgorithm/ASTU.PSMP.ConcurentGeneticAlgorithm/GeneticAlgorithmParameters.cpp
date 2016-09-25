#include "GeneticAlgorithmParameters.h"



GeneticAlgorithmParameters::GeneticAlgorithmParameters()
{
}


GeneticAlgorithmParameters::~GeneticAlgorithmParameters()
{
}

int GeneticAlgorithmParameters::GetInitialPopulationSize()
{
	return initialPopulationSize;
}

int GeneticAlgorithmParameters::GetGenerationCount()
{
	return generationCount;
}

int GeneticAlgorithmParameters::GetReproductionNumber()
{
	return reproductionNumber;
}

double GeneticAlgorithmParameters::GetMutationProbability()
{
	return mutationProbability;
}

double GeneticAlgorithmParameters::GetGoodOrganizmSurvivalProbability()
{
	return goodOrganizmSurvivalProbability;
}

double GeneticAlgorithmParameters::GetBadOrganizmDeathProbability()
{
	return badOrganizmDeathProbability;
}

int GeneticAlgorithmParameters::GetOrganismStatesCount()
{
	return organismStatesCount;
}

void GeneticAlgorithmParameters::SetInitialPopulationSize(int initialPopulationSize)
{
	this->initialPopulationSize = initialPopulationSize;
}

void GeneticAlgorithmParameters::SetGenerationCount(int generationCount)
{
	this->generationCount = generationCount;
}

void GeneticAlgorithmParameters::SetReproductionNumber(int reproductionNumber)
{
	this->reproductionNumber = reproductionNumber;
}

void GeneticAlgorithmParameters::SetMutationProbability(double mutationProbability)
{
	this->mutationProbability = mutationProbability;
}

void GeneticAlgorithmParameters::SetGoodOrganizmSurvivalProbability(double goodOrganizmSurvivalProbability)
{
	this->goodOrganizmSurvivalProbability = goodOrganizmSurvivalProbability;
}

void GeneticAlgorithmParameters::SetBadOrganizmDeathProbability(double badOrganizmDeathProbability)
{
	this->badOrganizmDeathProbability = badOrganizmDeathProbability;
}

void GeneticAlgorithmParameters::SetOrganismStatesCount(int statesCount)
{
	this->organismStatesCount = statesCount;
}
