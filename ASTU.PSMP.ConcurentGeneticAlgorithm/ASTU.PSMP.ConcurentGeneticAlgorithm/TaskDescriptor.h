#pragma once
#include "Task.h"
#include <memory>
using namespace std;
class TaskDescriptor
{
public:
	TaskDescriptor(shared_ptr<Task> task);
	~TaskDescriptor();
	double GetFinishTime();
	void SetStartTime(double startTime);
	shared_ptr<Task> GetTask();
private:
	shared_ptr<Task> task;
	double startTime;
	bool completed = false;
};

