#pragma once
#include <vector>
#include <algorithm>
#include "Task.h"
using namespace std;
class TaskList
{
public:
	TaskList();
	~TaskList();
	Task* GetTaskByNumber(int taskNumber);
private:
	std::vector <Task*> taskList;
};

