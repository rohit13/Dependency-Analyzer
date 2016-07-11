//////////////////////////////////////////////////////////////////////////////////
//  DependencyAnalyzer.h   - Computes Dependency after type analyzing the file  //
//  ver 1.0                                                                     //
//  Language:				C++, Visual Studio 2105							    //
//  Platform:				Dell XPS L510X, Windows 10							//
//  Application:			Dependency Analysis								    //
//							CSE687 - Object Oriented Design						//
//  Author:					Rohit Sharma, Syracuse University					//
//							(315) 935-1323, rshar102@syr.edu					//
//////////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
Computes Dependency after analyzing the file

Public Interface functions:
WorkItem<WorkResult1> startDependencyAnalysis(std::string fs, std::unordered_map<std::string, TypeStore> mergeTT, std::vector<std::string> fileList);

Required Files:
ThreadPool.h,Utilities.h,Tokenizer.h,SemiExp.h
Parser.h,ActionsAndRules.h,ConfigureParser.h,Tasks.h
TypeStore.h, DataStore.h

Build Process:
==============

Build commands
devenv Project3_DependencyAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 9 April 16
*/
//
#pragma once
#include<conio.h>
#include<iomanip>
#include<iostream>
#include <unordered_map>
#include<vector>
#include "../DataStore/DataStore.h"
#include "../TypeTable/TypeStore.h"
#include "../ThreadPool/ThreadPool.h"

using WorkResult1 = std::vector<std::string>;

class DependencyAnalyzer {
public:
	WorkItem<WorkResult1> startDependencyAnalysis(std::string fs, std::unordered_map<std::string, TypeStore> mergeTT, std::vector<std::string> fileList);
};