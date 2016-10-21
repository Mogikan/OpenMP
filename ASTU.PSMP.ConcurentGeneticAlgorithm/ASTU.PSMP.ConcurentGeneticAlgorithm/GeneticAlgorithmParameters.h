#pragma once
class GeneticAlgorithmParameters
{
public:
	GeneticAlgorithmParameters();
	GeneticAlgorithmParameters(const GeneticAlgorithmParameters &original);
	~GeneticAlgorithmParameters();
	int GetInitialPopulationSize();
	int GetGenerationCount();
	int GetReproductionNumber();
	double GetMutationProbability();
	double GetGoodOrganizmSurvivalProbability();
	double GetBadOrganizmDeathProbability();
	int GetOrganismStatesCount();

	void SetInitialPopulationSize(int initialPopulationSize);
	void SetGenerationCount(int generationCount);
	void SetReproductionNumber(int reproductionNumber);
	void SetMutationProbability(double mutationProbability);
	void SetGoodOrganizmSurvivalProbability(double goodOrganizmSurvivalProbability);
	void SetBadOrganizmDeathProbability(double badOrganizmDeathProbability);
	void SetOrganismStatesCount(int statesCount);

private:
	int initialPopulationSize = 10;
	int generationCount = 100;
	int reproductionNumber = 3;
	int organismStatesCount = 2;//binaryOrganism
	double mutationProbability = 0.05;
	double goodOrganizmSurvivalProbability = 0.99;
	double badOrganizmDeathProbability = 0.95;
};

