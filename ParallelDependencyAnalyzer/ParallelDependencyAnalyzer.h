//////////////////////////////////////////////////////////////////////
//  ParallelDependencyAnalyzer.h - This package calls all required  //
//  packages of the project, and display dependencies				//
//  ver 1.0                                                         //
//  Language:     C++, Visual Studio 2105                           //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:		  Rohit Sharma, Syracuse University					//
//				  (315) 935-1323, rshar102@syr.edu					//
//////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This package calls all required packages of the project, merges type tables and display dependencies

Public Interface functions:
void startParallelDependencyAnalysis(DataStore dataStore, std::unordered_map<std::string, TypeStore> mergeTT, int numThreads);
void pushDependenciesInFile();

Build Process:
==============
Required files
- Parser.h, Parser.cpp, ScopeStack.h, ScopeStack.cpp,
ActionsAndRules.h, ActionsAndRules.cpp, ConfigureParser.cpp, Tokenizer.h, Tokenizer.cpp,
TypeTable.h,ThreadPool.h,TypeAnalyzer.h,Task.h,DependencyAnalyzer.h,
Utilities.h,SemiExp.h,SemiExp.cpp, ConfigureParser.h,Tasks.h, TypeStore.h, DataStore.h

Build commands
devenv Project3_DependencyAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 9 April 16
- start parallel dependency analysis
- push found dependencies in a file

*/
#pragma once
#include<unordered_map>
#include "../DataStore/DataStore.h"
#include "../TypeTable/TypeStore.h"

class ParallelDependencyAnalyzer {
private:
	std::unordered_map <std::string, std::vector<std::string>> depFile;
public:
	void startParallelDependencyAnalysis(DataStore dataStore, std::unordered_map<std::string, TypeStore> mergeTT, int numThreads);
	void pushDependenciesInFile();
};