#include "PCTaskDescriptorList.h"



PCTaskDescriptorList::PCTaskDescriptorList()
{
}




PCTaskDescriptorList::~PCTaskDescriptorList()
{
}

shared_ptr<PCTaskDescriptorList>  PCTaskDescriptorList::Clone()
{
	auto result = shared_ptr<PCTaskDescriptorList>(new PCTaskDescriptorList());
	for (int i = 0; i < taskDescriptorList.size(); i++)
	{
		result->AddTask(taskDescriptorList[i]->GetTask());
	}
	return result;
}


shared_ptr<TaskDescriptor> PCTaskDescriptorList::GetCurrentTask()
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

void PCTaskDescriptorList::AddTask(shared_ptr<Task> task)
{
	taskDescriptorList.push_back(shared_ptr<TaskDescriptor>(new TaskDescriptor(task)));
}
