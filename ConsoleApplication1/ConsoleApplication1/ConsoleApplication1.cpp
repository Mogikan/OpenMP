// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#pragma once;

#include "stdafx.h"
#include <list>
#include <iostream>
using namespace std;

int main()
{
	std::list<int> intlist;
	for (int i = 0; i < 10; i++)
	{
		intlist.push_back(i);
	}

	std::list<int>::iterator iterator,iteratorCopy;
	for (iterator = intlist.begin(); iterator != intlist.end(); ++iterator) {
		std::cout << *iterator;
	}


	bool breakIteration = false;
	for (iterator = intlist.begin(); iterator != intlist.end(); (breakIteration)?iterator:iterator++) 		
	{
		breakIteration = false;
		if ((*iterator) == 0)
		{
			breakIteration = true;
			iteratorCopy = iterator;
			if (iterator == intlist.begin())
			{
				iteratorCopy++;
			}
			else
			{
				iteratorCopy--;
			}		
			
			intlist.splice(intlist.end(), intlist, iterator);
			iterator = iteratorCopy;			
		}
		std::cout << *iterator;
	}
	std::cin.ignore();
}

