#include "tn_money.h"
#include "tn_number.h"
#include "tn_util.h"

map<wstring, std::string> coin_map = {
        {L"$", "dollar"},
        {L"£", "pound"},
        {L"€", "euro"},
        {L"￥", "yuan"}

};
bool IsDollar(string& s) {
    string cur_s = s;
     if (cur_s.size() <= 1)
         return false;
     if (cur_s.size() > 3 && cur_s.substr(cur_s.size() - 3) == "trn")
         cur_s = cur_s.substr(0, cur_s.size() - 3);
     else if (cur_s.size() > 2 && cur_s.substr(cur_s.size() - 2) == "bn")
         cur_s = cur_s.substr(0, cur_s.size() - 2);
     else if (cur_s.size() > 1 && cur_s.substr(cur_s.size() - 1) == "m")
         cur_s = cur_s.substr(0, cur_s.size() - 1);
     wstring wcur_s = s2ws(s);
     string num = "";
     if (wcur_s.substr(0, 1) == L"$")
         num = cur_s.substr(1);
     else if (wcur_s.substr(wcur_s.size() - 1) == L"$")
         num = cur_s.substr(0, cur_s.size() - 1);
     if (num.empty())
         return false;
     else
        return IsDigit(num) || IsDigitWithComma(num) || IsDecimal(num);
}
// 处理英文$的读法
string ProcessDollar(string& s) {
    if (s.size() <= 1)
        return s;
    string cur_s = s;
    string res = "";
    wstring wcur_s = s2ws(s);
    if (wcur_s.substr(0, 1) == L"$")
        cur_s = cur_s.substr(1);
    else if (wcur_s.substr(wcur_s.size() - 1) == L"$")
        cur_s = cur_s.substr(0, cur_s.size() - 1);
    string num = "";
    if (cur_s.size() > 3 && cur_s.substr(cur_s.size() - 3) == "trn") {
        num = cur_s.substr(0, cur_s.size() - 3);
        res += ConvertNum2Eng(num) + " trillion dollars";
    }
    else if (cur_s.size() > 2 && cur_s.substr(cur_s.size() - 2) == "bn") {
        num = cur_s.substr(0, cur_s.size() - 2);
        res += ConvertNum2Eng(num) + " billion dollars";
    }
    else if (cur_s.size() > 1 && cur_s.substr(cur_s.size() - 1) == "m") {
        num = cur_s.substr(0, cur_s.size() - 1);
        res += ConvertNum2Eng(num) + " million dollars";
    }
    if (res != "")
        return res;
    num = cur_s;
    if (IsZero(num))
        res += "zero dollars";
    else if (IsDigit(num) || IsDigitWithComma(num)) {
        if (num == "1")
            res += "one dollar";
        else
            res += ConvertInt2Eng(num) + " dollars";
    } else if (IsDecimal(num)) {
        vector<string> split_num = SplitString(num, ".");
        if (!IsZero(split_num[1]) && split_num[1].size() >= 3) {
            res += ConvertDemical2Eng(num) + " dollars";
            return res;
        }
        if (split_num[0] != "0") {
            if (split_num[0] == "1")
                res += "one dollar";
            else
                res += ConvertInt2Eng(split_num[0]) + " dollars";
            if (!IsZero(split_num[1]))
                res += " and";
        }
        if (!IsZero(split_num[1])) {
            if (split_num[1].size() == 1) {
                split_num[1] += "0";
                res += " " + ConvertInt2Eng(split_num[1]) + " cents";
            } else {
                if (split_num[1] == "01")
                    res += " one cent";
                else
                    res += " " + ConvertInt2Eng(split_num[1]) + " centes";
            }
        }
    }
    return trim(res);
}
