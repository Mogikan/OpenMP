#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "Task.h"
using namespace std;
class TaskGraph
{
public:
	TaskGraph();
	~TaskGraph();
	static TaskGraph* FromFile(std::string filePath);
	int GetTasksCount();
private:
	std::vector<Task*> taskGraph;
};

