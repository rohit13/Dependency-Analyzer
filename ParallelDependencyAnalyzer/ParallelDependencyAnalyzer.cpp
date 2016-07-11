//////////////////////////////////////////////////////////////////////
//  ParallelDependencyAnalyzer.cpp - This package calls all required//
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
#include "ParallelDependencyAnalyzer.h"
#include "../Task/Task.h"
#include "../ThreadPool/ThreadPool.h"
#include "../Utilities/Utilities.h"
#include "../DependencyAnalyzer/DependencyAnalyzer.h"
#include "../TypeAnalyzer/TypeAnalyzer.h"
#include "..//FileMgr/FileSystem.h"
#include <fstream>

#define DEP_TABLE "./Outputs/DepTable_Output_Threaded.txt"
#define Util StringHelper;
using WorkResult1 = std::vector<std::string>;
using namespace Utilities;

//----< method to start parallel dependency analysis using task package>--------------------------------
void ParallelDependencyAnalyzer::startParallelDependencyAnalysis(DataStore dataStore, std::unordered_map<std::string, TypeStore> mergeTT, int numThreads)
{
	Task<WorkResult1> task;
	std::vector<std::string> depVector;
	ProcessWorkItem<WorkResult1> processorDep;
	task.startThreads(processorDep, numThreads);
	std::vector<std::string> fileList;
	std::cout<<std::endl;
	StringHelper::Title("Starting dependency analysis on following files:",'=');
	for (std::vector<std::string>::iterator i = dataStore.begin(); i != dataStore.end(); i++) {
		std::cout << std::endl << *i;
		fileList.push_back(*i);
	}
	for (std::string fs : fileList) {
		DependencyAnalyzer depAnal;
		WorkItem<WorkResult1> wi2 = depAnal.startDependencyAnalysis(fs,mergeTT,fileList);
		task.enqueueTask(processorDep, &wi2);
		depVector = task.fetchResult(processorDep);
		for (std::string dep : depVector) {
			std::cout << std::endl << dep;			
		}
		if (depFile.find(fs) == depFile.end()) {
			depFile.emplace(fs, depVector);
		}
		else {
			std::vector<std::string> temp = depFile.find(fs)->second;
			for (std::string dep : depVector) {
				temp.push_back(dep);
			}
			depFile.find(fs)->second = temp;
		}
	}
	pushDependenciesInFile();
	task.endTasks(processorDep);
	task.waitTask(processorDep);
}

//----< method to push dependencies in a file>--------------------------------
void ParallelDependencyAnalyzer::pushDependenciesInFile() {
	std::fstream file;
	std::string filePath =DEP_TABLE; //check if "./test.cpp" exists
	std::string fpath = FileSystem::Path::getFullFileSpec(filePath);
	std::ifstream ifile(filePath);
	file.open(DEP_TABLE, std::ios::out);
	for (auto it = depFile.begin(); it != depFile.end();it++) {
		file <<std::endl<< "* "<<it->first<<std::endl;
		for (std::string dep : it->second) {
			file << std::setw(10) << "- " << dep << std::endl;
		}
	}
	std::cout << std::endl <<std::endl<< "Dependency Table is stored at location: " << fpath << std::endl;
	file.close();
}

#ifdef PARALLEL_DEP
int main() {
	DataStore dataStore;
	dataStore.save("E:\\Object Oriented Design\\Project3_DependencyAnalyzer\\Inputs\\FileA.cpp");
	dataStore.save("E:\\Object Oriented Design\\Project3_DependencyAnalyzer\\Inputs\\FileB.cpp");
	int numThreads = 4;
	TypeAnalyzer typeAnal;
	std::unordered_map<std::string, TypeStore> mergeTT;
	mergeTT = typeAnal.startTypeAnalysis(dataStore, numThreads);
	ParallelDependencyAnalyzer dep;
	dep.startParallelDependencyAnalysis(dataStore, mergeTT,numThreads);
}
#endif