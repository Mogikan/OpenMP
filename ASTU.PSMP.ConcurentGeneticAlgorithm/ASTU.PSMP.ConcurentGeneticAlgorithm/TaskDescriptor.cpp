#include "TaskDescriptor.h"

TaskDescriptor::TaskDescriptor(Task * task)
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

double TaskDescriptor::SetStartTime(double startTime)
{
	this->startTime = startTime;
	completed = true;
}

Task * TaskDescriptor::GetTask()
{
	return task;
}
