#include <iostream>
#include "ParallelBalanceAlgorithm.h"
#include <memory>
#include <time.h>
using namespace std;

int main()
{
	cout << "Started\n\r";
	srand(time(NULL));
	std::shared_ptr<GeneticAlgorithmParameters> geneticParameters(new GeneticAlgorithmParameters());
	geneticParameters->SetInitialPopulationSize(120);
	geneticParameters->SetGenerationCount(100);
	geneticParameters->SetReproductionNumber(30);	
	geneticParameters->SetMutationProbability(0.05);
	geneticParameters->SetGoodOrganizmSurvivalProbability(0.95);
	geneticParameters->SetBadOrganizmDeathProbability(0.99);

	std::shared_ptr<TaskList> taskList(TaskList::FromFile("graphdata.txt"));
	int islandsCount = 5;
	int migrationCount = 20;
	std::unique_ptr<ParallelBalanceAlgorithm> algorithm(new ParallelBalanceAlgorithm(geneticParameters, taskList, islandsCount, migrationCount));
	algorithm->Execute();
	cout << "done";
	cin.get();
	return 0;
}
