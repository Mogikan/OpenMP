#pragma once

class Organism
{
public:	
	Organism(int statesCount,int length);
	Organism(int* organismGenes, int statesCount);
	~Organism();
	Organism* Mutate();
	virtual Organism* CreateOrganism(int* genes, int statesCount) = 0;
	virtual double MeasureFitness() = 0;
private:
	int* organismGenes;
	int GetLength();
	int statesCount;	
};

