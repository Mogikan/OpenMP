#include <vector>
#pragma once
class Task
{
public:
	Task(double executionTime,int taskNumber);
	~Task();
	int GetTaskNumber();
	double GetExecutionTime();
	std::vector < Task* > GetPrecedingTasks();
private:
	double taskNumber;
	std::vector<Task*> precedingTasks;
	double executionTime;
};

