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
