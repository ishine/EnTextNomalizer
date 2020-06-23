#ifndef TEXT_NORM_ENG_TN_UTIL_H
#define TEXT_NORM_ENG_TN_UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<string> SplitString(const string& s, const string& c);
int CountStr(const string& s, const char& c);
string trim(string& s);
wstring s2ws(const string& s);
string ws2s(const wstring& ws);
bool IsString(string& s);
string Upper2Lower(string& text);
bool IsUpper(string& s);
string& strip(string &s, string c);

#endif //TEXT_NORM_ENG_TN_UTIL_H
