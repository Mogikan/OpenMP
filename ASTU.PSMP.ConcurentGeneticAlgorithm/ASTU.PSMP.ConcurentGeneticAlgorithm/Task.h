#pragma once;
#include <vector>
#include <memory>
using namespace std;

class Task
{
public:
	Task();
	Task(double executionTime,int taskNumber);	
	~Task();
	int GetTaskNumber();
	double GetExecutionTime();
	void SetExecutionTime(double executionTime);
	void SetTaskNumber(int taskNumber);
	std::vector <shared_ptr<Task>> GetPrecedingTasks();
	void AddPrecedingTask(shared_ptr<Task> task);
private:
	int taskNumber;
	std::vector<shared_ptr<Task>> precedingTasks;
	double executionTime;
};

