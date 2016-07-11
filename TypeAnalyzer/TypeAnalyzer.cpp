#define _CRT_SECURE_NO_WARNINGS
/////////////////////////////////////////////////////////////////////////
//  TypeAnalyzer.cpp - Provides functionality to do type analysis on   //
//						provided files								   //
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
This package contains a functionality to do type anyalysis on provided files

Public Interface functions:
std::unordered_map<std::string, TypeStore> startTypeAnalysis(DataStore dataStore, int numThreads);
void showTypeTableOnConsole(std::unordered_map<std::string, TypeStore> map1);
void mergeTypeTables(std::unordered_map<std::string, TypeStore> map1);
void pushTTinFile();

Required Files:
TypeAnalyzer.h
ThreadPool.h
ConfigureParser.h
Parser.h
Tokenizer.h
SemiExp.h
Utilities.h
TypeTable.h
Tasks.h
DataStore.h
TypeStore.h

Build commands
devenv Project3_DependencyAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 9 April 16
*/
//
#include "TypeAnalyzer.h"
#include "../Utilities/Utilities.h"
#include "../ThreadPool/ThreadPool.h"
#include "../Parser/ConfigureParser.h"
#include "../DataStore/DataStore.h"
#include "../TypeTable/TypeStore.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "../Task/Task.h"
#include "../FileMgr/FileSystem.h"
#include <fstream>

#define Util StringHelper
#define TYPE_TABLE "./Outputs/TypeTable_Output_Threaded.txt"
using namespace Utilities;
using WorkResult = std::unordered_map<std::string, TypeStore>;

//----< method to do type analysis>--------------------------------
std::unordered_map<std::string, TypeStore> TypeAnalyzer::startTypeAnalysis(DataStore dataStore, int numThreads)
{
	Task<WorkResult> task;
	ProcessWorkItem<WorkResult> processor;
	task.startThreads(processor, numThreads);
	// define work item
	std::unordered_map<std::string, TypeStore> map1;
	for (auto fs : dataStore) {
		WorkItem<WorkResult> wi1 = [fs]() {
			std::cout << std::endl << "==================================="<<std::endl;
			std::cout<<"Type Analysis of file = " + fs + " on thread "<<std::this_thread::get_id();
			ConfigParseToConsole configure;
			Repository* repos;
			std::unordered_map<std::string, TypeStore> map;
			Parser* pParser = configure.Build(fs);
			try {
				if (pParser) {
					if (!configure.Attach(fs)) {
						std::cout << std::endl << "Could not open file " << fs << std::endl;
					}
				}
				else {
					std::cout << std::endl << " Parser not built" << std::endl;
				}
				// now that parser is built, use it
				while (pParser->next())
					pParser->parse();
				std::cout << std::endl;
			}
			catch (std::exception& ex) {
				std::cout << std::endl << std::endl << ex.what() << std::endl << std::endl;
			}
			repos = configure.getRepository();
			map = repos->getTypeTable()->getTypeTable();
			return map;
		};
		task.enqueueTask(processor,&wi1);
		map1 = task.fetchResult(processor);
		showTypeTableOnConsole(map1);
		mergeTypeTables(map1);
	}
	pushTTinFile();
	task.endTasks(processor);
	task.waitTask(processor);
	return mergeTT;
}

//----< method to show type table on console>--------------------------------
void TypeAnalyzer::showTypeTableOnConsole(std::unordered_map<std::string, TypeStore> map1) {
	for (auto it = map1.begin(); it != map1.end(); it++) {
		std::vector<std::pair<std::string, std::string>> output = it->second.getFileNsPair();
		for (int i = 0; i < output.size(); i++)
		{
			std::cout << "\n" << std::left << std::setw(20) << it->first << std::setw(20) << it->second.getTypeName();
			std::cout << std::setw(80) << output[i].first;
			std::cout << std::setw(20) << output[i].second << std::endl;
		}
	}
}

//----< method to merge type tables>--------------------------------
void TypeAnalyzer::mergeTypeTables(std::unordered_map<std::string, TypeStore> map1) {
	for (auto it = map1.begin(); it != map1.end(); it++) {
		if (mergeTT.find(it->first) == mergeTT.end()) {
			mergeTT.emplace(it->first, it->second);
		}
		else {
			std::vector<std::pair<std::string, std::string>> _mergedPair = mergeTT.find(it->first)->second.getFileNsPair();
			std::vector<std::pair<std::string, std::string>> _pair = it->second.getFileNsPair();
			for (std::pair<std::string, std::string> p : _pair) {
				_mergedPair.push_back(p);
			}
			mergeTT.find(it->first)->second.setFileNsPair(_mergedPair);
		}
	}
}

//----< method to push type table in file>--------------------------------
void TypeAnalyzer::pushTTinFile()
{
	std::fstream file;
	std::string filePath = TYPE_TABLE; //check if "./test.cpp" exists
	std::string fpath = FileSystem::Path::getFullFileSpec(filePath);
	std::ifstream ifile(filePath);
	file.open(TYPE_TABLE,std::ios::out);
	for (auto it = mergeTT.begin(); it != mergeTT.end(); it++) {
		file<<"\n"<<std::left << std::setw(25) <<it->first;
		file << std::setw(25) << it->second.getTypeName();
		std::vector<std::pair<std::string, std::string>> output = it->second.getFileNsPair();
	
			for (int i = 0; i < output.size(); i++)
			{
				if (i== 0) {
					file << std::setw(100) << output[0].first;
					file << std::setw(25) << output[0].second;
				}
				else {
					file << std::endl<<std::left << std::setw(50) << " ";
					file << std::setw(100) << output[i].first;
					file << std::setw(25) << output[i].second;
				}
			}	
	}
	std::cout << std::endl << "Type Table is stored at location: " << fpath <<std::endl;
	file.close();
}

#ifdef TYPE_ANAL
int main() {
	DataStore dataStore;
	dataStore.save("E:\\Object Oriented Design\\Project3_DependencyAnalyzer\\Inputs\\FileA.cpp");
	dataStore.save("E:\\Object Oriented Design\\Project3_DependencyAnalyzer\\Inputs\\FileB.cpp");
	int numThreads = 4;
	TypeAnalyzer type;
	type.startTypeAnalysis(dataStore,numThreads);
}
#endif