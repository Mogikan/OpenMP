#include "PCTaskDescriptorList.h"



PCTaskDescriptorList::PCTaskDescriptorList()
{
}


PCTaskDescriptorList::~PCTaskDescriptorList()
{
}


TaskDescriptor * PCTaskDescriptorList::GetCurrentTask()
{
	return taskDescriptorList.at(currentIndex);
}

void PCTaskDescriptorList::ConsumeTask(double taskStartTime)
{
	this->GetCurrentTask()->SetStartTime(taskStartTime);
	consumedTime = this->GetCurrentTask()->GetFinishTime();
	currentIndex++;
}

bool PCTaskDescriptorList::HasNotConsumedTask()
{
	return currentIndex < taskDescriptorList.size();
}

double PCTaskDescriptorList::GetConsumedTime()
{
	return consumedTime;
}

void PCTaskDescriptorList::AddTask(Task * task)
{
	taskDescriptorList.push_back(new TaskDescriptor(task));
}
