/////////////////////////////////////////////////////////////////////////
//  TypeStore.cpp - Provides functionality to serve as custom datatype //
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
TypeStore.h
TypeTable.h

Build Process:
==============

Build commands
devenv Project3_DependencyAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 9 April 16
*/
//

#include "TypeStore.h"
#include "TypeTable.h"

TypeStore::TypeStore()
{
}

TypeStore::~TypeStore()
{	
}

//----< method to get type name>--------------------------------
std::string TypeStore::getTypeName()
{
	return _typeName;
}

//----< method to set type name>--------------------------------
void TypeStore::setTypeName(std::string typeName)
{
	_typeName = typeName;
}

//----< method to get file namespace pair>--------------------------------
std::vector<std::pair<std::string, std::string>> TypeStore::getFileNsPair()
{
	return _fileNsPair;
}

//----< method to set file namespace pair>--------------------------------
void TypeStore::setFileNsPair(std::vector<std::pair<std::string, std::string>> fileNsPair)
{
	_fileNsPair = fileNsPair;
}

#ifdef TYPE_STORE
int main() {
	std::unordered_map<std::string, TypeStore> typeTableMap;
	TypeStore *typeStore = new TypeStore;
	typeStore->setTypeName("test");
	std::vector<std::pair<std::string, std::string>> _pair;
	std::pair<std::string, std::string> pair = std::make_pair("testFile.txt", "GNS");
	_pair.push_back(pair);
	typeStore->setFileNsPair(_pair);
	typeTableMap.emplace("abc", *typeStore);
	for (auto it = typeTableMap.begin(); it != typeTableMap.end(); it++) {
		std::cout << "\nKey: " << it->first;
	}
	return 0;
}
#endif