/////////////////////////////////////////////////////////////////////////
//  TypeTable.cpp - Provides functionality to serve as custom datatype //
//			        of storing details of type analysis				   //
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
This package contains a functionality to serve as custom datatype of storing details of type analysis

Public Interface functions:
TypeTable();
~TypeTable();
void setValue(std::string key, std::string type, std::string filename, std::string nameSpace);
std::unordered_map<std::string, TypeStore> getTypeTable();

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
#include<utility>

TypeTable::TypeTable()
{
}

TypeTable::~TypeTable()
{
}

//----< method to set value in type table>--------------------------------
void TypeTable::setValue(std::string key, std::string type, std::string filename, std::string nameSpace)
{
	if (typeTableMap.find(key) == typeTableMap.end())
	{
		TypeStore *typeStore = new TypeStore;
		typeStore->setTypeName(type);
		std::vector<std::pair<std::string, std::string>> _pair;
		std::pair<std::string, std::string> pair = std::make_pair(filename, nameSpace);
		_pair.push_back(pair);
		typeStore->setFileNsPair(_pair);
		typeTableMap.emplace(key, *typeStore);
	}
	else {
		TypeStore *typeStore = &typeTableMap[key];
		typeStore->setTypeName(type);
		std::vector<std::pair<std::string, std::string>> _pair = typeStore->getFileNsPair();
		std::pair<std::string, std::string> pair = std::make_pair(filename, nameSpace);
		_pair.push_back(pair);
		typeStore->setFileNsPair(_pair);
	}
}

//----< method to get type table>--------------------------------
std::unordered_map<std::string, TypeStore> TypeTable::getTypeTable()
{
	return typeTableMap;
}

#ifdef TYPE_TABLE
int main() {
	TypeTable* t= new TypeTable;
	t->setValue("A", "Member Function", "E:\\Object Oriented Design\\Project3_DependencyAnalyzer\\Inputs\\FileA.cpp", "GNS");
	std::unordered_map<std::string, TypeStore> TypeTable = t->getTypeTable();
	for (auto it = TypeTable.begin(); it != TypeTable.end(); it++) {
		std::cout << "\nKey: " << it->first;
	}
}
#endif
