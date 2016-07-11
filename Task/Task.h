#ifndef TASK_H
#define TASK_H
/////////////////////////////////////////////////////////////////////////
//  Task.h - Serves as a wrapper on top of ThreadPool class			   //
//  ver 1.0                                                            //
//  Language:				C++, Visual Studio 2015					   //
//  Platform:				Dell XPS L510X, Windows 10				   //
//  Application:			Dependency Analysis						   //
//							CSE687 - Object Oriented Design			   //
//  Author:					Rohit Sharma, Syracuse University		   //
//							(315) 935-1323, rshar102@syr.edu		   //
/////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This package contains a functionality to interface with ThreadPool

Public Interface functions:
void enqueueTask(ProcessWorkItem<Result>& processorObj, WorkItem<Result>* pWi);
Result fetchResult(ProcessWorkItem<Result>& processorObj);
void waitTask(ProcessWorkItem<Result>& processorObj);
void endTasks(ProcessWorkItem<Result>& processorObj);
void startThreads(ProcessWorkItem<Result>& processorObj, int numOfThreads);

Build Process:
==============

Build commands
- devenv Project3_DependencyAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 9 April 16
*/
//
#pragma once
#include<conio.h>
#include<iomanip>
#include<unordered_map>
#include<functional>
#include "../TypeTable/TypeTable.h"
#include "../TypeTable/TypeStore.h"
#include "../ThreadPool/ThreadPool.h"

template<typename Result>
using WorkItem = std::function<Result()>;

template<typename Result>
class Task {
private:

public:
	void enqueueTask(ProcessWorkItem<Result>& processorObj, WorkItem<Result>* pWi);
	Result fetchResult(ProcessWorkItem<Result>& processorObj);
	void waitTask(ProcessWorkItem<Result>& processorObj);
	void endTasks(ProcessWorkItem<Result>& processorObj);
	void startThreads(ProcessWorkItem<Result>& processorObj, int numOfThreads);
};

//----< method to enqueue workitems in blocking queue>--------------------------------
template<typename Result>
void Task<Result>::enqueueTask(ProcessWorkItem<Result>& processorObj, WorkItem<Result>* pWi)
{
	processorObj.doWork(pWi);
}

//----< method to enqueue fetch result of a workitem from queue>--------------------------------
template<typename Result>
Result Task<Result>::fetchResult(ProcessWorkItem<Result>& processorObj)
{
	return processorObj.result();
}

//----< method to wait for other threads>--------------------------------
template<typename Result>
void Task<Result>::waitTask(ProcessWorkItem<Result>& processorObj)
{
	processorObj.wait();
}

//----< method to finish all started threads>--------------------------------
template<typename Result>
void Task<Result>::endTasks(ProcessWorkItem<Result>& processorObj)
{
	processorObj.doWork(nullptr);
}

//----< method to start provided number of threads>--------------------------------
template<typename Result>
void Task<Result>::startThreads(ProcessWorkItem<Result>& processorObj, int numOfThreads)
{
	processorObj.start(numOfThreads);
}

#endif