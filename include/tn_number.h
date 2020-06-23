#ifndef TEXT_NORM_ENG_TN_NUMBER_H
#define TEXT_NORM_ENG_TN_NUMBER_H

#include "tn_util.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

bool IsDigit(string& s);
bool IsDigitWithComma(string& s);
bool IsDecimal(string& s);
bool IsFraction(string& s);
bool IsOrdinal(string& s);
bool IsZero(string& s);
bool IsPercent(string& s);
string Digit2Str(int& int_temp);
int Str2Int(string &s);
string BasicConvertFunc(string& num);
string ConvertInt2Eng(string& num);
string ConvertDemical2Eng(string& num);
string ConvertOrdinal2Eng(string& s);
string ConvertFraction2Eng(string& s);
string ConvertNum2Eng(string& s);

#endif //TEXT_NORM_ENG_TN_NUMBER_H
