/////////////////////////////////////////////////////////////////////
//  Task.cpp - Cpp file for Task.h file						       //
//  ver 1.o                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
//	Author:		   Rohit Sharma, Syracuse University			   //
//                 (315) 935-1323, rshar102@syr.edu				   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module uses test stub to test public interfaces defined
in Task.h .

Build Process:
==============
Required files:
Task.h

build command:
devenv Project3_DependencyAnalyzer.sln /rebuild debug

*/


#include "Task.h"

using Work = std::string;
#ifdef TASK
int main() {
	ProcessWorkItem<Work> processor1;
	Task<Work> task;
	task.startThreads(processor1,2);
	//Building a work item
	WorkItem<Work> wi2 = []() {
		return "Hello";
	};
	task.enqueueTask(processor1, &wi2); // enqueuing work item
	std::cout << task.fetchResult(processor1);
	task.waitTask(processor1); // Waiting for thread process to complete
	task.endTasks(processor1);
	return 0;
}
#endif