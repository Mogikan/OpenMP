#include <iostream>
#include "ParallelBalanceAlgorithm.h"
#include <memory>
#include <time.h>
using namespace std;

int main()
{
	cout << "Hello world\n";
	srand(time(NULL));
	std::shared_ptr<GeneticAlgorithmParameters> geneticParameters(new GeneticAlgorithmParameters());
	geneticParameters->SetInitialPopulationSize(10);
	geneticParameters->SetGenerationCount(100);
	geneticParameters->SetReproductionNumber(3);	
	geneticParameters->SetMutationProbability(0.05);
	geneticParameters->SetGoodOrganizmSurvivalProbability(0.99);
	geneticParameters->SetBadOrganizmDeathProbability(0.95);

	std::shared_ptr<TaskList> taskList(TaskList::FromFile("graphdata.txt"));
	int islandsCount = 5;
	int migrationCount = 10;
	std::unique_ptr<ParallelBalanceAlgorithm> algorithm(new ParallelBalanceAlgorithm(geneticParameters, taskList, islandsCount, migrationCount));
	algorithm->Execute();
	cin.get();
	return 0;
}
