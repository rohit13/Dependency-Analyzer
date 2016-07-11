#pragma once
/////////////////////////////////////////////////////////////////////
//  ThreadPool.h - Defines ThreadPool class creating and managing  //
//					threads										   //
//  ver 3.0                                                        //
//  Lanaguage:     Visual C++ 2005                                 //
//  Platform:      Dell Dimension 9150, Windows XP SP2             //
//	Application:   Project#2 - CSE 687-Object Oriented Design	   //
//  Source:        Jim Fawcett, CST 2-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
//  Author:        Rohit Sharma, Syracuse University			   //
//                 (315) 935-1323, rshar102@syr.edu		           //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
Defines ThreadPool class for parallel processing

Public Interface:
=================
void save(const std::string& filespec)
void save(const std::string& filename, const std::string& path)
iterator begin()
iterator end()

Build Process:
==============
Required files
Build commands (either one)
- devenv Project3_DependencyAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 3.0 : 9 Apr 16
- changed ~ProcessWorkItem, start(), and wait() to handle multiple threads and closing threads.
ver 2.0 : 17 Mar 16
-changed documentation
ver 1.0 : 12 Feb 15
- first release
*/

#include <thread>
#include <functional>
#include "BlockingQueue.h"

#define DEFAULT_NUM_OF_THREADS 5

template<typename Result>
using WorkItem = std::function<Result()>;

///////////////////////////////////////////////////////////////////////
// class to process work items
// - each work item is processed sequentially on a single child thread

template<typename Result>
class ProcessWorkItem
{
public:
	void start(int numOfThreads = DEFAULT_NUM_OF_THREADS);
	void doWork(WorkItem<Result>* pWi);
	Result result();
	void wait();
	~ProcessWorkItem();
private:
	std::vector<std::thread*> _pThread;
	BlockingQueue<WorkItem<Result>*> _workItemQueue;
	BlockingQueue<Result> _resultsQueue;
};
//----< wait for child thread to terminate >---------------------------

template<typename Result>
void ProcessWorkItem<Result>::wait()
{
	//added wait for multiple threads
	for (std::thread* _thread : _pThread) {
		_thread->join();
	}
}
//----< enqueue work item >--------------------------------------------

template<typename Result>
void ProcessWorkItem<Result>::doWork(WorkItem<Result>* pWi)
{
	_workItemQueue.enQ(pWi);
}
//----< retrieve results with blocking call >--------------------------

template<typename Result>
Result ProcessWorkItem<Result>::result()
{
	return _resultsQueue.deQ();
}
//----< start child thread that dequeus work items >-------------------

template<typename Result>
void ProcessWorkItem<Result>::start(int numOfThreads)
{
	std::function<void()> threadProc =
		[&]() {
		while (true)
		{
			WorkItem<Result>* pWi = _workItemQueue.deQ();
			if (pWi == nullptr)
			{
				_workItemQueue.enQ(nullptr);//enqueues nullptr task to do cascaded stopping of threads
				std::cout << "\n  Shutting down work item processing on thread "<< std::this_thread::get_id();
				return;
			}
			Result result = (*pWi)();
			_resultsQueue.enQ(result);
		}
	};
	for (int i = 0; i < numOfThreads; i++) {
		_pThread.push_back(new std::thread(threadProc));
	}
}
//----< clean up heap >------------------------------------------------

template<typename Result>
ProcessWorkItem<Result>::~ProcessWorkItem()
{
	//delete all threads
	for (std::thread* _thread : _pThread) {
		delete _thread;
	}
}


