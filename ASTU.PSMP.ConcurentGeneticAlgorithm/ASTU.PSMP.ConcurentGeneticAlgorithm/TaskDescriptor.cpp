#include "TaskDescriptor.h"

TaskDescriptor::TaskDescriptor(shared_ptr<Task> task)
{
	this->task = task;
}

TaskDescriptor::~TaskDescriptor()
{
}

double TaskDescriptor::GetFinishTime()
{
	return startTime + task->GetExecutionTime();
}

void TaskDescriptor::SetStartTime(double startTime)
{
	this->startTime = startTime;
	completed = true;
}

shared_ptr<Task> TaskDescriptor::GetTask()
{
	return task;
}
