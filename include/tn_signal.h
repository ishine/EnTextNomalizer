#ifndef TEXT_NORM_ENG_TN_SIGNAL_H
#define TEXT_NORM_ENG_TN_SIGNAL_H

#include "tn_util.h"
bool IsGreek(wstring& s);
bool IsRuler(string& s);
string ProcessGreek(string& text);
string SplitRuler(string& s);
string Ruler2Eng(string& s);
string Signal2Eng(string& s);
string RemovePuncs(string& s);
#endif //TEXT_NORM_ENG_TN_SIGNAL_H
