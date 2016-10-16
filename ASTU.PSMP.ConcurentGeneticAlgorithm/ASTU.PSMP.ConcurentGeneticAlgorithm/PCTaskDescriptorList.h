#pragma once
#include "TaskDescriptorList.h"
class PCTaskDescriptorList :
	public TaskDescriptorList
{
public:
	PCTaskDescriptorList();
	~PCTaskDescriptorList();
	TaskDescriptor* GetCurrentTask();
	void ConsumeTask(double taskStartTime);
	bool HasNotConsumedTask();
	double GetConsumedTime();
private:
	int currentIndex = 0;
	double consumedTime;
};

