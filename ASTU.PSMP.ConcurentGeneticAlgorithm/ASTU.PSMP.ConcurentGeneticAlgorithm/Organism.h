#pragma once

class Organism
{
public:

Organism();
	~Organism();
	virtual Organism* Mutate() = 0;
	virtual Organism* CreateOrganism() = 0;
	virtual double MeasureFitness() = 0;	
};

