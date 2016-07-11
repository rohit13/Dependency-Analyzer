#ifndef TYPETABLE_H
#define TYPETABLE_H
/////////////////////////////////////////////////////////////////////////
//  TypeTable.h - Provides functionality to serve as custom datatype   //
//			      of storing details of type analysis				   //
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
This package contains a functionality to to serve as custom datatype of storing details of type analysis

Public Interface functions:
TypeTable();
~TypeTable();
void setValue(std::string key, std::string type, std::string filename, std::string nameSpace);
std::unordered_map<std::string, TypeStore> getTypeTable();

Required Files:
TypeStore.h

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
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include"TypeStore.h"

class TypeTable {
public:
	TypeTable();
	~TypeTable();
	void setValue(std::string key, std::string type, std::string filename, std::string nameSpace);
	std::unordered_map<std::string, TypeStore> getTypeTable();
private:
	std::unordered_map<std::string, TypeStore> typeTableMap;
};
#endif