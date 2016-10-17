#include "TaskList.h"



TaskList::TaskList()
{
}


TaskList::~TaskList()
{
}

Task * TaskList::GetTaskByNumber(int taskNumber)
{
	std::vector<Task*>::iterator iterator = std::find_if(taskList.begin(), taskList.end(), [taskNumber](Task* task) -> bool { return task->GetTaskNumber() == taskNumber; });
	return *iterator;
}
