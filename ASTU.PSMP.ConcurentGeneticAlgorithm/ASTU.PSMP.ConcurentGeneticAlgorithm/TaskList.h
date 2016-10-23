#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <memory>
#include "Task.h"
using namespace std;
class TaskList
{
public:
	TaskList();
	TaskList(std::vector<shared_ptr<Task>> tasks);
	~TaskList();
	std::vector <shared_ptr<Task>> GetAllTasks();
	int Size();
	shared_ptr<Task> GetTaskByNumber(int taskNumber);
	static shared_ptr<TaskList> FromFile(std::string filePath);
private:
	std::vector <shared_ptr<Task>> taskList;
};

