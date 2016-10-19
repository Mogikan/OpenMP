#include "PCTaskDescriptorList.h"



PCTaskDescriptorList::PCTaskDescriptorList()
{
}




PCTaskDescriptorList::~PCTaskDescriptorList()
{
}

PCTaskDescriptorList * PCTaskDescriptorList::Clone()
{
	auto result = new PCTaskDescriptorList();
	for (int i = 0; i < taskDescriptorList.size(); i++)
	{
		result->AddTask(taskDescriptorList.at(i)->GetTask());
	}
	return result;
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
