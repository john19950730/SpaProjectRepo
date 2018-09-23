#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>    // std::transform

using namespace std;

class Result {
public:
	virtual pair < map<string, vector<string>>, bool > toComparableFormat() = 0;
	virtual bool isSelectSynonymFound(string selectSynonym) = 0;
	virtual vector<string> getSynonyms() = 0;
	void printMap();
};

class BooleanResult : public Result {
public:
	BooleanResult(bool result);
	bool getResult();
	pair < map<string, vector<string>>, bool > toComparableFormat();
	bool isSelectSynonymFound(string selectSynonym);
	vector<string> getSynonyms();
private:
	bool result;
};

class IntVectorResult : public Result {
public:
	IntVectorResult(vector<unsigned int> result, string synonym);
	vector<unsigned int> getResult();
	pair < map<string, vector<string>>, bool > toComparableFormat();
	bool isSelectSynonymFound(string selectSynonym);
	vector<string> getSynonyms();
private:
	vector<unsigned int> result;
	string synonym;
};

class StringVectorResult : public Result {
public:
	StringVectorResult(vector<string> result, string synonym);
	vector<string> getResult();
	pair < map<string, vector<string>>, bool > toComparableFormat();
	bool isSelectSynonymFound(string selectSynonym);
	vector<string> getSynonyms();
private:
	vector<string> result;
	string synonym;
};

class IntIntPairVectorResult : public Result {
public:
	IntIntPairVectorResult(vector<pair<unsigned int, unsigned int>> result, pair<string, string> synonym);
	vector<pair<unsigned int, unsigned int>> getResult();
	pair < map<string, vector<string>>, bool > toComparableFormat();
	bool isSelectSynonymFound(string selectSynonym);
	vector<string> getSynonyms();
private:
	vector<pair<unsigned int, unsigned int>> result;
	pair<string, string> synonym;
};

class IntStringPairVectorResult : public Result {
public:
	IntStringPairVectorResult(vector<pair<unsigned int, string>> result, pair<string, string> synonym);
	vector<pair<unsigned int, string>> getResult();
	pair < map<string, vector<string>>, bool > toComparableFormat();
	bool isSelectSynonymFound(string selectSynonym);
	vector<string> getSynonyms();
private:
	vector<pair<unsigned int, string>> result;
	pair<string, string> synonym;
};

class StringStringPairVectorResult : public Result {
public:
	StringStringPairVectorResult(vector<pair<string, string>> result, pair<string, string> synonym);
	vector<pair<string, string>> getResult();
	pair < map<string, vector<string>>, bool > toComparableFormat();
	bool isSelectSynonymFound(string selectSynonym);
	vector<string> getSynonyms();
private:
	vector<pair<string, string>> result;
	pair<string, string> synonym;
};