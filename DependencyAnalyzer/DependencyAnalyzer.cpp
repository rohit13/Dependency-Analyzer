//////////////////////////////////////////////////////////////////////////////////
//  DependencyAnalyzer.cpp - Computes Dependency after analyzing the file       //
//  ver 1.0                                                                     //
//  Language:          C++, Visual Studio 2105							        //
//	Platform:		   Dell XPS L510X - Windows 10								//
//  Application:       Parallel Dependency Analysis						     	//
//				       CSE687 - Object Oriented Design						    //
//  Author:            Rohit Sharma -Syracuse University - rshar102@syr.edu     //
//								                                                //
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
#define _CRT_SECURE_NO_WARNINGS
#include "DependencyAnalyzer.h"
#include "../Utilities/Utilities.h"
#include "../ThreadPool/ThreadPool.h"
#include "../Parser/ConfigureParser.h"
#include "../DataStore/DataStore.h"
#include "../TypeTable/TypeStore.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "../TypeAnalyzer/TypeAnalyzer.h"
#include "../Task/Task.h"
#define Util StringHelper

using namespace Scanner;
using namespace Utilities;
using WorkResult1 = std::vector<std::string>;

//----< method to do dependency analysis for each file - called from parallel dep analysis>--------------------------------
WorkItem<WorkResult1> DependencyAnalyzer::startDependencyAnalysis(std::string fs, std::unordered_map<std::string, TypeStore> mergeTT, std::vector<std::string> fileList)
{
		WorkItem<WorkResult1> wi2 = [fs, mergeTT, fileList]() {
			std::cout << "\n\nFinding Dependency : working on thread " << std::this_thread::get_id();
			std::unordered_map<std::string, bool> depFiles;
			for (auto file : fileList) {
				auto it = depFiles.find(file);
				if (it != depFiles.end())
					it->second = false;
				else
					depFiles.emplace(file, false);
			}
			std::ifstream in(fs);
			Toker toker;
			toker.returnComments(false);
			toker.attach(&in);
			std::cout << "\n===============================" << std::endl;
			std::cout << std::endl << "Filename: " << fs << std::endl;
			std::cout << "===============================" << std::endl;
			std::cout << "Depends on: " << std::endl;
			std::vector<std::string> depVectorWork;
			do
			{
				std::string tok = toker.getTok();
				std::unordered_map<std::string, TypeStore> mergeTTMutable = mergeTT;
				for (auto it = mergeTTMutable.begin(); it != mergeTTMutable.end(); ++it) {
					if (tok == it->first) {
						std::vector<std::pair<std::string, std::string>> dependents = it->second.getFileNsPair();
						for (int i = 0; i < dependents.size(); i++)
						{
							if (fs != dependents[i].first && !depFiles.find(dependents[i].first)->second) {
								depVectorWork.push_back(dependents[i].first);
								depFiles.find(dependents[i].first)->second = true;
							}
						}
					}
				}
			} while (in.good());
			return depVectorWork;
		};
		return wi2;
}

#ifdef DEP_ANAL
int main() {
	DataStore dataStore;
	dataStore.save("E:\\Object Oriented Design\\Project3_DependencyAnalyzer\\Inputs\\FileA.cpp");
	dataStore.save("E:\\Object Oriented Design\\Project3_DependencyAnalyzer\\Inputs\\FileB.cpp");
	int numThreads = 4;
	TypeAnalyzer typeAnal;
	std::unordered_map<std::string, TypeStore> mergeTT;
	mergeTT = typeAnal.startTypeAnalysis(dataStore, numThreads);
	for (auto it = dataStore.begin(); it != dataStore.end();it++) {
		DependencyAnalyzer depAnal;
		WorkItem<WorkResult1> wi2 = depAnal.startDependencyAnalysis(*it, mergeTT, dataStore.getStore());
		std::cout << "\nwork item received";
	}
}
#endif