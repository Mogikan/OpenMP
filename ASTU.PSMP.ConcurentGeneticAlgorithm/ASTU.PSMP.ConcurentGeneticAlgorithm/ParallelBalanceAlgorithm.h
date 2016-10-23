#pragma once
#include "LoadBalancingAlgorithm.h"
#include <vector>
#include <memory>
class ParallelBalanceAlgorithm
{
public:
	ParallelBalanceAlgorithm(shared_ptr<GeneticAlgorithmParameters> geneticParameters, shared_ptr<TaskList> tasklist, int islandsCount, int migrationCount);
	~ParallelBalanceAlgorithm();
	void Execute();
private:
	shared_ptr<GeneticAlgorithmParameters> geneticParameters;
	std::vector<shared_ptr<LoadBalancingAlgorithm>> islands;
	shared_ptr<TaskList> tasklist;
	int migrationCount;
	int islandsCount;
};

