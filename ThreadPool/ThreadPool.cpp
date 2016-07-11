/////////////////////////////////////////////////////////////////////
//  ThreadPool.cpp - Defines ThreadPool class creating and managing//
//					threads										   //
//  Lanaguage:     Visual C++ 2005                                 //
//  Platform:      Dell Dimension 9150, Windows XP SP2             //
//	Application:   Project#3 - CSE 687-Object Oriented Design	   //
//  Source:        Jim Fawcett, CST 2-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
//  Author:        Rohit Sharma, Syracuse University			   //
//                 (315) 935-1323, rshar102@syr.edu		           //
/////////////////////////////////////////////////////////////////////
/*
 A single child thread processes work items equeued by main thread
Module Operations:
==================
Defines ThreadPool class for parallel processing

Public Interface:
=================
none. provides test stub for ThreadPool.h

Build Process:
==============
Required files
Build commands (either one)
- devenv Project3_DependencyAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 2.0 : 17 Mar 16
-changed documentation
ver 1.0 : 12 Feb 15
- first release
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <conio.h>
#include "ThreadPool.h"
#include "../Utilities/Utilities.h"
#include "../FileMgr/FileMgr.h"
#include "../DataStore/DataStore.h"
#include <iostream>
#include "../ParallelDependencyExecutive/ParallelDependencyExecutive.h"
#include "../FileMgr/FileSystem.h"
#include "../Parser/ConfigureParser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Tokenizer/Tokenizer.h"
#include<iomanip>

//----< demonstrate ProcessWorkItem class >----------------------------

using Util = Utilities::StringHelper;
using WorkResult = std::string;


#ifdef T_POOL
int main()
{
	Util::Title("Enqueued Work Items");
	std::cout << "\n  main thread id = " << std::this_thread::get_id();
	ProcessWorkItem<WorkResult> processor;
	processor.start(4);
	// define 1st work item
	WorkItem<WorkResult> wi1 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi1";
	};
	processor.doWork(&wi1);
	// define 2nd work item
	WorkItem<WorkResult> wi2 = []()
	{
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		size_t sum = 0;
		for (size_t i = 0; i < 100000; ++i)
			sum += i;
		return "wi2 result = " + Utilities::Converter<size_t>::toString(sum);
	};
	processor.doWork(&wi2);
	// the following calls to result() block until results are enqueued
	std::cout << "\n  " << processor.result();
	std::cout << "\n  " << processor.result();
	processor.doWork(nullptr);
	// wait for child thread to complete
	processor.wait();
	std::cout << "\n\n";
	return 0;
}
#endif