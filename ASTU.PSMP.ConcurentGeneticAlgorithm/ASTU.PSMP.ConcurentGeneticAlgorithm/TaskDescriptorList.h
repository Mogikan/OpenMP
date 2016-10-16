#pragma once
#include <vector>
#include <algorithm>
#include "TaskDescriptor.h"
class TaskDescriptorList
{
public:
	TaskDescriptorList();
	~TaskDescriptorList();
	TaskDescriptor* GetTaskDescriptorByTaskNumber(int taskNumber);
protected:
	std::vector <TaskDescriptor*> taskDescriptorList;
};

