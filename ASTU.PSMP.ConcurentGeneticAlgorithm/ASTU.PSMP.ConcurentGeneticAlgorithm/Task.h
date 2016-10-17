#include <vector>
#pragma once
class Task
{
public:
	Task();
	Task(double executionTime,int taskNumber);	
	~Task();
	int GetTaskNumber();
	double GetExecutionTime();
	void SetExecutionTime(double executionTime);
	std::vector < Task* > GetPrecedingTasks();
	void AddPrecedingTask(Task* task);
private:
	double taskNumber;
	std::vector<Task*> precedingTasks;
	double executionTime;
};

