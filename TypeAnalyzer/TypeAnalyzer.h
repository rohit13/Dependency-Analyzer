#ifndef TYPEANALYZER_H
#define TYPEANALYZER_H
/////////////////////////////////////////////////////////////////////////
//  TypeAnalyzer.h - Provides functionality to do type analysis on	   //
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
#pragma once
#include<string>
#include<conio.h>
#include<iomanip>
#include<iostream>
#include "../DataStore/DataStore.h"
#include "../TypeTable/TypeStore.h"
#include <unordered_map>

class TypeAnalyzer {
public:
	std::unordered_map<std::string, TypeStore> startTypeAnalysis(DataStore dataStore, int numThreads);
	void showTypeTableOnConsole(std::unordered_map<std::string, TypeStore> map1);
	void mergeTypeTables(std::unordered_map<std::string, TypeStore> map1);
	void pushTTinFile();
private:
	std::unordered_map<std::string, TypeStore> mergeTT;
};
#endif