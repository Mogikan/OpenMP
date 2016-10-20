#include "TaskDescriptorList.h"



TaskDescriptorList::TaskDescriptorList()
{
}


TaskDescriptorList::~TaskDescriptorList()
{
}



TaskDescriptor * TaskDescriptorList::GetTaskDescriptorByTaskNumber(int taskNumber)
{
	std::vector<TaskDescriptor*>::iterator iterator = std::find_if(taskDescriptorList.begin(), taskDescriptorList.end(), [taskNumber](TaskDescriptor* taskDescriptor) -> bool { return taskDescriptor->GetTask()->GetTaskNumber() == taskNumber; });
	if (iterator == taskDescriptorList.end())
	{
		return nullptr;
	}
	return *iterator;
}

int TaskDescriptorList::GetTaskIndex(int taskNumber)
{
	std::vector<TaskDescriptor*>::iterator iterator = std::find_if(taskDescriptorList.begin(), taskDescriptorList.end(), [taskNumber](TaskDescriptor* taskDescriptor) -> bool { return taskDescriptor->GetTask()->GetTaskNumber() == taskNumber; });
	return iterator - taskDescriptorList.begin();
}

TaskDescriptor * TaskDescriptorList::GetTaskAtIndex(int index)
{
	return taskDescriptorList[index];
}

int TaskDescriptorList::Size()
{
	return this->taskDescriptorList.size();
}

void TaskDescriptorList::ReplaceTaskDescriptor(int index, TaskDescriptor * task)
{
	taskDescriptorList[index] = task;
}

void TaskDescriptorList::RemoveTaskDescriptorAtIndex(int index)
{	
	taskDescriptorList.erase(taskDescriptorList.begin() + index);
}

bool TaskDescriptorList::ContainsTask(int taskNumber)
{
	return std::find_if(taskDescriptorList.begin(), taskDescriptorList.end(), [taskNumber](TaskDescriptor* taskDescriptor) -> bool { return taskDescriptor->GetTask()->GetTaskNumber() == taskNumber; }) != taskDescriptorList.end();
}
