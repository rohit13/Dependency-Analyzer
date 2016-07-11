/////////////////////////////////////////////////////////////////////
//  ParallelDependencyExecutive.h - This class defines getFiles and//
//						executeParsing methods.					   //
//						Starting point for application.			   //
//  ver 1.0                                                        //
//  Lanaguage:     C++ Visual Studio 2015                          //
//  Platform:      Dell XPS L510X - Windows 10		               //
//	Application:   Project#3 - CSE 687-Object Oriented Design	   //
//  Author:        Rohit Sharma, Syracuse University			   //
//                 (315) 935-1323, rshar102@syr.edu		           //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This class defines getFiles and executeParsing methods.Starting point for application.

Public Interface:
=================
int getFiles(int argc, char* argv[]); // method to get files
void demonstrateReqs(); // method to demonstrate all requirements
void demonstrateReq68Output(SyntaxTree* treeRoot); //method to demo output of requirements 6 and 8
void executeParsing(); // method to execute parsing on each file found at given directory path
int main(int argc, char* argv[]) //main method to start application with.

Build Process:
==============
Required files
Build commands (either one)
- devenv Project3_DependencyAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 17 Mar 16
- first release
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "../FileMgr/FileMgr.h"
#include "ParallelDependencyExecutive.h"
#include "../DataStore/DataStore.h"
#include "../FileMgr/FileSystem.h"
#include "../Parser/ConfigureParser.h"
#include "../Utilities/Utilities.h"
#include "../Parser/ActionsAndRules.h"
#include "../Tokenizer/Tokenizer.h"
#include "../ThreadPool/ThreadPool.h"
#include "../TypeAnalyzer/TypeAnalyzer.h"
#include "../DependencyAnalyzer/DependencyAnalyzer.h"
#include "../ParallelDependencyAnalyzer/ParallelDependencyAnalyzer.h"
#include<conio.h>
#include<iomanip>
#include<cstdlib>

#define Util StringHelper
using namespace Utilities;
using namespace Scanner;

//----< method to demonstrate all requirements>--------------------------------
void ParallelDependencyExecutive::demonstrateReqs() {
	StringHelper::title("Demonstrating - Requirement 3");
	std::cout << std::endl;
	std::cout << std::endl << " Provided a Repository program that provides a checkin process";
	std::cout << std::endl << " Each checkin will support copying and providing metadata for all files in the Repository" << std::endl;
	StringHelper::title("Demonstrating - Requirement 5");
	std::cout << std::endl;
	std::cout << std::endl << " Each checkin will create a new directory with a unique name based on the file name and checkin-date"<<std::endl;
	std::cout << std::endl << " Each checkin directory contains checkin metadata containing dependencies among files" << std::endl; 
	StringHelper::title("Demonstrating - Requirement 6");
	std::cout << std::endl;
	std::cout << " Each checkin directory have a boolean status property with value as open/closed."<< std::endl;
	StringHelper::title("Demonstrating - Requirement 7");
	std::cout << std::endl;
	std::cout << std::endl << " Provided an extraction process for modules or packages with or without dependencies."<< std::endl;
	StringHelper::title("Demonstrating - Requirement 8");
	std::cout << std::endl;
	std::cout << std::endl << " Provided a message-passing communication system used to access the Repository's functionality from another process or machine.";
	StringHelper::title("Demonstrating - Requirement 9");
	std::cout << std::endl;
	std::cout << std::endl << " Communication system supports for passing HTTP style messages using asynchronous one-way messaging"<< std::endl;
	StringHelper::title("Demonstrating - Requirement 10");
	std::cout << std::endl;
	std::cout << std::endl << " Communication system supports sending and receiving streams of bytes. Streams will be established with an initial exchange of messages."<<std::endl;
	StringHelper::title("Demonstrating - Requirement 11");
	std::cout << std::endl;
	std::cout << std::endl << " Automated unit test suite provided that exercises all the file placed inside TestFiles folder in project demonstrating that I met all requirements." << std::endl;
	_getch();
}

//----< method to get files from the specified directory>--------------------------------
int ParallelDependencyExecutive::getFiles(int argc, char* argv[]) {
	StringHelper::Title(" Searching for files", '=');
	if (argc < 2)
	{
		std::cout << std::endl << " Please enter the directory and pattern on command line to search for files.\n\n";
		return 1;
	}
	std::cout << std::endl << " Provided directory path to look for files is: " << argv[1];
	std::cout << std::endl << " Provided text pattern is: " << argv[2];
	StringHelper::Title("Following files were found", '-');
	FileMgr fileMgr(argv[1], dataStore);
	std::vector<char*> patternVec;
	char* patternArr = strtok(argv[2], ",");
	while (patternArr)
	{
		patternVec.push_back(patternArr);
		patternArr = strtok(NULL, ",");
	}
	for (size_t n = 0; n < patternVec.size(); ++n)
	{
		fileMgr.addPattern(patternVec[n]);
	}
	fileMgr.search();
	return 0;
}

//----< method to executer Type Analysis and Dependency Analysis on the found files>--------------------------------
void ParallelDependencyExecutive::executeParsing(char* argv[]) {
	std::unordered_map<std::string, TypeStore> mergeTT;
	
	int numThreads = atoi(argv[3]);
	TypeAnalyzer typeAnal;
	mergeTT = typeAnal.startTypeAnalysis(dataStore, numThreads);

	ParallelDependencyAnalyzer parallelDepAnal;
	parallelDepAnal.startParallelDependencyAnalysis(dataStore, mergeTT, numThreads);
	
}
#ifdef TEST_METRIC
int main(int argc, char* argv[]) {
	ParallelDependencyExecutive me;
	me.demonstrateReqs();
	if (me.getFiles(argc, argv)) {
		return 1;
	}
	me.executeParsing(argv);
}

#endif