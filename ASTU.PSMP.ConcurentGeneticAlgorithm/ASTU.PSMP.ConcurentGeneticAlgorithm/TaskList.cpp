#include "TaskList.h"



TaskList::TaskList()
{
}

TaskList::TaskList(std::vector<shared_ptr<Task>> tasks)
{
	this->taskList = tasks;
}


TaskList::~TaskList()
{
}

std::vector<shared_ptr<Task>> TaskList::GetAllTasks()
{
	return this->taskList;
}

int TaskList::Size()
{
	return taskList.size();
}

shared_ptr<Task> TaskList::GetTaskByNumber(int taskNumber)
{
	auto iterator = std::find_if(taskList.begin(), taskList.end(), [taskNumber](shared_ptr<Task> task) -> bool { return task->GetTaskNumber() == taskNumber; });
	return *iterator;
}

shared_ptr<TaskList> TaskList::FromFile(std::string filePath)
{
	std::ifstream infile(filePath);
	std::string line;
	std::vector<shared_ptr<Task>> graph;
	std::getline(infile, line);
	std::istringstream linestream(line);
	int taskCount;
	double taskExecutionTime;
	linestream >> taskCount;
	for (int i = 0; i < taskCount; i++)
	{
		auto task = shared_ptr<Task>(new Task());
		task->SetTaskNumber(i);
		graph.push_back(task);
	}
	for (int i = 0; i < taskCount; i++)
	{
		std::getline(infile, line);
		std::istringstream linestream(line);
		linestream >> taskExecutionTime;
		graph[i]->SetExecutionTime(taskExecutionTime);
		int connectedTask;
		while (linestream >> connectedTask)
		{
			graph[connectedTask]->AddPrecedingTask(graph[i]);
		}
	}
	return shared_ptr<TaskList>(new TaskList(graph));
}
