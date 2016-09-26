#pragma once

class Organism
{
public:	
	Organism(int statesCount,int length);
	Organism(int* organismGenes, int statesCount);
	~Organism();
	void Mutate();
	virtual double MeasureFitness() = 0;
private:
	int* organismGenes;
	int statesCount;	
};

