#include "TaskList.h"



TaskList::TaskList()
{
}

TaskList::TaskList(std::vector<Task*> tasks)
{
	this->taskList = tasks;
}


TaskList::~TaskList()
{
}

std::vector<Task*> TaskList::GetAllTasks()
{
	return this->taskList;
}

int TaskList::Size()
{
	return taskList.size();
}

Task * TaskList::GetTaskByNumber(int taskNumber)
{
	std::vector<Task*>::iterator iterator = std::find_if(taskList.begin(), taskList.end(), [taskNumber](Task* task) -> bool { return task->GetTaskNumber() == taskNumber; });
	return *iterator;
}

TaskList * TaskList::FromFile(std::string filePath)
{
	std::ifstream infile("tasklist.txt");
	std::string line;
	std::vector<Task*> graph;
	std::getline(infile, line);
	std::istringstream linestream(line);
	int taskCount;
	double taskExecutionTime;
	linestream >> taskCount;
	for (int i = 0; i < taskCount; i++)
	{
		graph.push_back(new Task());
	}
	for (int i = 0; i < taskCount; i++)
	{
		std::getline(infile, line);
		std::istringstream linestream(line);
		linestream >> taskExecutionTime;
		graph.at(i)->SetExecutionTime(taskExecutionTime);
		int connectedTask;
		while (linestream >> connectedTask)
		{
			graph.at(connectedTask)->AddPrecedingTask(graph.at(i));
		}
		return new TaskList(graph);
	}
}
