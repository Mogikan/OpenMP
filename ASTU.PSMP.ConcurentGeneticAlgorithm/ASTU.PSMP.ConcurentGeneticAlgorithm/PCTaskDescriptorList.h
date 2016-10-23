#pragma once
#include <memory>
#include "TaskDescriptorList.h"
using namespace std;
class PCTaskDescriptorList :
	public TaskDescriptorList
{
public:
	PCTaskDescriptorList();
	~PCTaskDescriptorList();
	shared_ptr<PCTaskDescriptorList> Clone();
	shared_ptr<TaskDescriptor> GetCurrentTask();
	void ConsumeTask(double taskStartTime);
	bool HasNotConsumedTask();
	double GetConsumedTime();
	void AddTask(shared_ptr<Task> task);
private:
	int currentIndex = 0;
	double consumedTime;
};

