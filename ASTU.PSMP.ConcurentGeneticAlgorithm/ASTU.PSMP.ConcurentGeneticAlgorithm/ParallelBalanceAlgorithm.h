#pragma once
#include "LoadBalancingAlgorithm.h"
#include <vector>
class ParallelBalanceAlgorithm
{
public:
	ParallelBalanceAlgorithm(GeneticAlgorithmParameters * geneticParameters, TaskList * tasklist, int islandsCount, int migrationCount);
	~ParallelBalanceAlgorithm();
private:
	GeneticAlgorithmParameters* geneticParameters;
	std::vector<LoadBalancingAlgorithm*> islands;
	TaskList* tasklist;
	int migrationCount;
};

