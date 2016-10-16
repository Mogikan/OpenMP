#include "TaskDescriptorList.h"



TaskDescriptorList::TaskDescriptorList()
{
}


TaskDescriptorList::~TaskDescriptorList()
{
}

TaskDescriptor * TaskDescriptorList::GetTaskDescriptorByTaskNumber(int taskNumber)
{
	std::find_if(taskDescriptorList.begin(), taskDescriptorList.end(), [taskNumber](TaskDescriptor* taskDescriptor) -> bool { return taskDescriptor->GetTask()->GetTaskNumber() == taskNumber; });
}
