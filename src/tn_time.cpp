#include "tn_time.h"
#include "tn_util.h"
#include "tn_number.h"

bool IsTime(string& s) {
    if (s.find(":") == -1) return false;
    vector<string> split_num = SplitString(s, ":");
    if (split_num.size() == 3 && IsDigit(split_num[0]) && IsDigit(split_num[1]) && IsDigit(split_num[2])) {
        int l = stoi(split_num[0]);
        int mid = stoi(split_num[1]);
        int r = stoi(split_num[2]);
        if (l >= 0 && l <= 24 && mid >= 0 && mid <= 60 && r >= 0 && r <= 60)
            return true;
    }
    if (split_num.size() == 2 && IsDigit(split_num[0]) && IsDigit(split_num[1])) {
        int l = stoi(split_num[0]);
        int r = stoi(split_num[2]);
        if (l >= 0 && l <= 24 && r >= 0 && r <= 60)
            return true;
    }
    return false;
}
// 处理时间的读法
// 对于9:30可以读为nine thirty，也可读为half past nine, 9:10可以读为ten past nine, 11:45可以读为a quater to twelve
// 目前采用Google翻译里转换的方式，仅处理为对应的数字读法
string ProcessTime(string& s) {
    string res = "";
    vector<string> split_num = SplitString(s, ":");
    res += ConvertInt2Eng(split_num[0]) + " ";
    if (split_num[1] == "00") {
        if (split_num.size() == 2) res += "o'clock ";
        else res += ConvertInt2Eng(split_num[1]) + " ";
    } else {
        res += ConvertInt2Eng(split_num[1]) + " ";
    }
    if (split_num.size() == 3) {
        res += ConvertInt2Eng(split_num[2]) + " ";
    }
    if (!res.empty())
        return res;
    return s;
}

bool IsDate(string& s) {
    string tmp_s = s;
    if (s.size() < 4 || s.size() > 5) return false;
    if (s.size() == 5) {
        if (s[s.size() - 1] == 's')
            tmp_s = tmp_s.substr(0, 4);
        else
            return false;
    }
    return IsDigit(tmp_s);
}

// 处理年份的读法，采用Google的方式，对于四位数来说当第一位数字是1或2，最后两个数非00时，判断为年份，拆分为两个数字来读
string ProcessDate(string& s) {
    string res = "";
    string tmp_s = s;
    if (tmp_s[tmp_s.size() - 1] == 's')
        tmp_s = tmp_s.substr(0, tmp_s.size() - 1);
    if (tmp_s[0] == '1' || tmp_s[0] == '2') {
        if (tmp_s.substr(1) == "000")
            res += ConvertInt2Eng(tmp_s);
        else {
            string l = tmp_s.substr(0,2);
            string r = tmp_s.substr(2);
            if (r == "00")
                res += ConvertInt2Eng(l) + " hundred";
            else if (r[0] == '0')
                res += ConvertInt2Eng(l) + " oh " + ConvertInt2Eng(r);
            else
                res += ConvertInt2Eng(l) + " " + ConvertInt2Eng(r);
        }
    } else {
        res += ConvertInt2Eng(tmp_s);
    }
    if (s[s.size() - 1] == 's') {
        res += "'s";
    }
    if (!res.empty())
        return res;
    return s;
}
