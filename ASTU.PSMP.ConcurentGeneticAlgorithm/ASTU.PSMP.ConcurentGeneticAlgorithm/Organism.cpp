#include "Organism.h"
#include <cstdlib>

using namespace std;

Organism::Organism(int statesCount,int length)
{
	organismGenes = new int[length];
	for (int i = 0; i < length; i++)
	{		
		organismGenes[i] = rand() % statesCount;
	}
}

Organism::Organism(int * organismGenes, int statesCount)
{
	this->organismGenes = organismGenes;
	this->statesCount = statesCount;
}


Organism::~Organism()
{	
	delete[] organismGenes;
}

Organism* Organism::Mutate()
{	
	int* newOrganismGenes = new int[GetLength()];
	for (int i = 0; i < GetLength(); i++)
	{
		int oldState = organismGenes[i];
		int newState;
		do 
		{
			 newState = rand() % statesCount;
		} 
		while (newState == oldState);
		newOrganismGenes[i] = newState;
		
	}
	return CreateOrganism(newOrganismGenes, statesCount);	
}

int Organism::GetLength()
{
	return sizeof(organismGenes)/sizeof(organismGenes[0]);
}
