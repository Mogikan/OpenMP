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
	int GetTaskIndex(int taskNumber);
	TaskDescriptor* GetTaskAtIndex(int index);
	void ReplaceTaskDescriptor(int index, TaskDescriptor* task);
	bool ContainsTask(int taskNumber);
protected:
	std::vector <TaskDescriptor*> taskDescriptorList;
};

