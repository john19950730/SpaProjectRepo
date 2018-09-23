#include "Result.h"

/*** BooleanResult ***/

void Result::printMap()
{
	auto map = this->toComparableFormat().first;
	for (auto i = map.cbegin(); i != map.cend(); ++i)
	{
		cout << " " << i->first << " | ";
		auto vctr = i->second;
		for (auto j = vctr.rbegin(); j != vctr.rend(); ++j)
		{
			cout << *j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

BooleanResult::BooleanResult(bool result)
{
	this->result = result;
	//this->result = true;
}

bool BooleanResult::getResult()
{
	return this->result;
}

pair < map<string, vector<string>>, bool > BooleanResult::toComparableFormat() {
	pair <map<string, vector<string>>, bool> convertedResult;
	convertedResult.second = this->result;

	return convertedResult;
}

bool BooleanResult::isSelectSynonymFound(string selectSynonym) {
	return false;	// shouldn't reach here 
}

vector<string> BooleanResult::getSynonyms() {
	return vector<string>();
}

/*** IntVectorResult ***/

IntVectorResult::IntVectorResult(vector<unsigned int> result, string synonym)
{
	this->result = result;
	this->synonym = synonym;
	//this->result = { 1, 2, 4, 4, 5, 7 };
	//this->synonym = "a";
}

vector<unsigned int> IntVectorResult::getResult()
{
	return this->result;
}

pair < map<string, vector<string>>, bool > IntVectorResult::toComparableFormat() {
	vector<string> s;
	pair < map<string, vector<string>>, bool > convertedResult;
	map<string, vector<string>> map;

	if (result.empty()) {
		convertedResult.second = false;
		return convertedResult;
	}

	for (unsigned int i : result) {
		s.push_back(to_string(i));
	}
	map[synonym] = s;
	convertedResult.first = map;
	convertedResult.second = true;

	return convertedResult;
}

bool IntVectorResult::isSelectSynonymFound(string selectSynonym) {
	return selectSynonym == this->synonym;
}

vector<string> IntVectorResult::getSynonyms() {
	vector<string> s;
	s.push_back(this->synonym);

	return s;
}

/*** StringVectorResult ***/

StringVectorResult::StringVectorResult(vector<string> result, string synonym)
{
	this->result = result;
	this->synonym = synonym;
	//this->result = { "p", "q", "r", "s", "s", "t", "w" };
	//this->synonym = "v";
}

vector<string> StringVectorResult::getResult()
{
	return this->result;
}

pair < map<string, vector<string>>, bool > StringVectorResult::toComparableFormat() {
	vector<string> s;
	pair < map<string, vector<string>>, bool > convertedResult;
	map<string, vector<string>> map;

	if (result.empty()) {
		convertedResult.second = false;
		return convertedResult;
	}

	for (string i : result) {
		s.push_back(i);
	}
	map[synonym] = s;
	convertedResult.first = map;
	convertedResult.second = true;

	return convertedResult;
}

bool StringVectorResult::isSelectSynonymFound(string selectSynonym) {
	return selectSynonym == this->synonym;
}

vector<string> StringVectorResult::getSynonyms() {
	vector<string> s;
	s.push_back(this->synonym);
	return s;
}

/*** IntIntPairVectorResult ***/

IntIntPairVectorResult::IntIntPairVectorResult(vector<pair<unsigned int, unsigned int>> result, pair<string, string> synonym)
{
	this->result = result;
	this->synonym = synonym;
	//this->result = { make_pair(1, 2), make_pair(3, 4), make_pair(6, 7), make_pair(7, 8) };
	//this->synonym = make_pair("s1", "s2");
}

vector<pair<unsigned int, unsigned int>> IntIntPairVectorResult::getResult()
{
	return this->result;
}

pair < map<string, vector<string>>, bool > IntIntPairVectorResult::toComparableFormat() {
	vector<string> s1;
	vector<string> s2;
	pair < map<string, vector<string>>, bool > convertedResult;
	map<string, vector<string>> map;

	if (result.empty()) {
		convertedResult.second = false;
		return convertedResult;
	}

	for (pair<unsigned int, unsigned int> i : result) {
		s1.push_back(to_string(i.first));
		s2.push_back(to_string(i.second));
	}
	map[synonym.first] = s1;
	map[synonym.second] = s2;
	convertedResult.first = map;
	convertedResult.second = true;

	return convertedResult;
}

bool IntIntPairVectorResult::isSelectSynonymFound(string selectSynonym) {
	return (selectSynonym == this->synonym.first || selectSynonym == this->synonym.second);
}

vector<string> IntIntPairVectorResult::getSynonyms() {
	vector<string> s;
	s.push_back(this->synonym.first);
	s.push_back(this->synonym.second);

	return s;
}

/*** IntStringPairVectorResult ***/

IntStringPairVectorResult::IntStringPairVectorResult(vector<pair<unsigned int, string>> result, pair<string, string> synonym)
{
	this->result = result;
	this->synonym = synonym;
	//this->result = { make_pair(3, "q"), make_pair(5, "r"), make_pair(5, "t"), make_pair(9, "q") };
	//this->synonym = make_pair("a", "v");
}

vector<pair<unsigned int, string>> IntStringPairVectorResult::getResult()
{
	return this->result;
}

pair < map<string, vector<string>>, bool > IntStringPairVectorResult::toComparableFormat() {
	vector<string> s1;
	vector<string> s2;
	pair < map<string, vector<string>>, bool > convertedResult;
	map<string, vector<string>> map;

	if (result.empty()) {
		convertedResult.second = false;
		return convertedResult;
	}

	for (pair<unsigned int, string> i : result) {
		s1.push_back(to_string(i.first));
		s2.push_back(i.second);
	}
	map[synonym.first] = s1;
	map[synonym.second] = s2;
	convertedResult.first = map;
	convertedResult.second = true;

	return convertedResult;
}

bool IntStringPairVectorResult::isSelectSynonymFound(string selectSynonym) {
	return (selectSynonym == this->synonym.first || selectSynonym == this->synonym.second);
}

vector<string> IntStringPairVectorResult::getSynonyms() {
	vector<string> s;
	s.push_back(this->synonym.first);
	s.push_back(this->synonym.second);
	
	return s;
}

/*** StringStringPairVectorResult ***/

StringStringPairVectorResult::StringStringPairVectorResult(vector<pair<string, string>> result, pair<string, string> synonym)
{
	this->result = result;
	this->synonym = synonym;
	//this->result = { make_pair("proc1", "w"), make_pair("proc1", "p"), make_pair("proc3", "p") };
	//this->synonym = make_pair("p", "v");
}

vector<pair<string, string>> StringStringPairVectorResult::getResult()
{
	return this->result;
}

pair < map<string, vector<string>>, bool > StringStringPairVectorResult::toComparableFormat() {
	vector<string> s1;
	vector<string> s2;
	pair < map<string, vector<string>>, bool > convertedResult;
	map<string, vector<string>> map;

	if (result.empty()) {
		convertedResult.second = false;
		return convertedResult;
	}

	for (pair<string, string> i : result) {
		s1.push_back(i.first);
		s2.push_back(i.second);
	}
	map[synonym.first] = s1;
	map[synonym.second] = s2;
	convertedResult.first = map;
	convertedResult.second = true;

	return convertedResult;
}

bool StringStringPairVectorResult::isSelectSynonymFound(string selectSynonym) {
	return (selectSynonym == this->synonym.first || selectSynonym == this->synonym.second);
}

vector<string> StringStringPairVectorResult::getSynonyms() {
	vector<string> s;
	s.push_back(this->synonym.first);
	s.push_back(this->synonym.second);

	return s;
}
