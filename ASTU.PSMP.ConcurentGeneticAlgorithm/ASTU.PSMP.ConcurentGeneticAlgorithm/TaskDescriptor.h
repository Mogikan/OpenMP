#pragma once
#include "Task.h"
class TaskDescriptor
{
public:
	TaskDescriptor(Task* task);
	~TaskDescriptor();
	double GetFinishTime();
	double SetStartTime(double startTime);
	Task* GetTask();
private:
	Task* task;
	double startTime;
	bool completed = false;
};

