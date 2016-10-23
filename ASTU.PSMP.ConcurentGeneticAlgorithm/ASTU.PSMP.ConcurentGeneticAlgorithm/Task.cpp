#include "Task.h"

Task::Task()
{
}

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

void Task::SetExecutionTime(double executionTime)
{
	this->executionTime = executionTime;
}

void Task::SetTaskNumber(int taskNumber)
{
	this->taskNumber = taskNumber;
}

std::vector<shared_ptr<Task>> Task::GetPrecedingTasks()
{
	return precedingTasks;
}

void Task::AddPrecedingTask(shared_ptr<Task> task)
{
	precedingTasks.push_back(task);
}
