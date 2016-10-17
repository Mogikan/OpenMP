#include "TaskGraph.h"



TaskGraph::TaskGraph()
{
}


TaskGraph::~TaskGraph()
{
}

TaskGraph * TaskGraph::FromFile(std::string filePath)
{
	std::ifstream infile("tasklist.txt");
	std::string line;
	std::vector<Task*> graph;
	std::getline(infile,line);
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
	}	
}

int TaskGraph::GetTasksCount()
{
	return taskGraph.size();
}
