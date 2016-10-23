#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include "TaskDescriptor.h"
using namespace std;
class TaskDescriptorList
{
public:
	TaskDescriptorList();
	~TaskDescriptorList();
	shared_ptr<TaskDescriptor> GetTaskDescriptorByTaskNumber(int taskNumber);
	int GetTaskIndex(int taskNumber);
	shared_ptr<TaskDescriptor> GetTaskAtIndex(int index);
	int Size();
	void ReplaceTaskDescriptor(int index, shared_ptr<TaskDescriptor> task);

	void RemoveTaskDescriptorAtIndex(int index);

	bool ContainsTask(int taskNumber);
protected:
	std::vector<shared_ptr<TaskDescriptor>> taskDescriptorList;
};

