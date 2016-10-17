#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Task.h"
using namespace std;
class TaskList
{
public:
	TaskList();
	TaskList(std::vector<Task*> tasks);
	~TaskList();
	std::vector < Task*> GetAllTasks();
	Task* GetTaskByNumber(int taskNumber);
	static TaskList* FromFile(std::string filePath);
private:
	std::vector <Task*> taskList;
};

