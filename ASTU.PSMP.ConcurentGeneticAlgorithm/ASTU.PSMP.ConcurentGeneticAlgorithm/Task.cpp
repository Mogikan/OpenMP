#include "Task.h"

Task::Task(double executionTime,int taskNumber)
{
	this->executionTime = executionTime;
	this->taskNumber = taskNumber;
}

Task::~Task()
{
}

int Task::GetTaskNumber()
{
	return this->taskNumber;
}

double Task::GetExecutionTime()
{
	return executionTime;
}

std::vector<Task*> Task::GetPrecedingTasks()
{
	return precedingTasks;
}
