#ifndef TYPESTORE_H
#define TYPESTORE_H
/////////////////////////////////////////////////////////////////////////
//  TypeStore.h - Provides functionality to serve as custom datatype   //
//			      in type table										   //
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
This package contains a functionality to serve as customer datatype in type table

Public Interface functions:
TypeStore();
~TypeStore();
std::string getTypeName();
void setTypeName(std::string typeName);
std::vector<std::pair<std::string, std::string>> getFileNsPair();
void setFileNsPair(std::vector<std::pair<std::string, std::string>> fileNsPair);

Required Files:
No File Required

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
#include<utility>
#include<vector>

class TypeStore {
public:
	TypeStore();
	~TypeStore();
	std::string getTypeName();
	void setTypeName(std::string typeName);
	std::vector<std::pair<std::string, std::string>> getFileNsPair();
	void setFileNsPair(std::vector<std::pair<std::string, std::string>> fileNsPair);
private:
	std::string _typeName;
	std::vector<std::pair<std::string, std::string>> _fileNsPair;
};
#endif