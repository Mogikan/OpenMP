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
	geneticParameters->SetInitialPopulationSize(50);
	geneticParameters->SetGenerationCount(100);
	geneticParameters->SetReproductionNumber(20);	
	geneticParameters->SetMutationProbability(0.02);
	geneticParameters->SetGoodOrganizmSurvivalProbability(0.99);
	geneticParameters->SetBadOrganizmDeathProbability(0.95);

	std::shared_ptr<TaskList> taskList(TaskList::FromFile("graphdata.txt"));
	int islandsCount = 1;
	int migrationCount = 1;
	std::unique_ptr<ParallelBalanceAlgorithm> algorithm(new ParallelBalanceAlgorithm(geneticParameters, taskList, islandsCount, migrationCount));
	algorithm->Execute();
	cout << "done";
	cin.get();
	return 0;
}
