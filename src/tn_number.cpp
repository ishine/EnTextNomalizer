//
// 将数字转为对应的英文读法，目前仅能处理合法的数字，不合法的数字符号等无法处理
//
#include "tn_number.h"

vector<string> indnum = {
        "zero", "one", "two", "three", "four", "five", "six",
        "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen",
        "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};
vector<string> decnum = {
        "twenty", "thirty", "forty", "fifty", "sixty","seventy", "eighty", "ninety"
};
vector<string> units = {"hundred", "thousand", "million", "billion"};
vector<string> ordinal = {"st", "nd", "rd", "th"};
map<string, string> ordinal_map = {
        {"zero", "zeroth"},
        {"one", "first"},
        {"two", "second"},
        {"three", "third"},
        {"four", "fourth"},
        {"five", "fifth"},
        {"six", "sixth"},
        {"seven", "seventh"},
        {"eight", "eighth"},
        {"nine", "nineth"},
        {"ten", "tenth"},
        {"eleven", "eleventh"},
        {"twelve", "twelfth"},
        {"thirteen", "thirteenth"},
        {"fourteen", "fourteenth"},
        {"fifteen", "fifteenth"},
        {"sixteen", "sixteenth"},
        {"seventeen", "seventeenth"},
        {"eighteen", "eighteenth"},
        {"nineteen", "nineteenth"},
        {"twenty", "twentieth"},
        {"thirty", "thirtieth"},
        {"fourty", "fourtieth"},
        {"fifty", "fiftieth"},
        {"sisty", "sixtieth"},
        {"seventy", "seventieth"},
        {"eighty", "eightieth"},
        {"ninety", "ninetieth"},
};
string g_dot = "point";
string g_negtive = "minus";
string g_positive = "plus";
string num_zero = "zero";
string num_oh = "oh";


// 判断字符串是否为纯数字
bool IsDigit(string& s) {
    if (s.empty())
        return false;
    for (auto c: s) {
        if (c < L'0' || c > L'9')
            return false;
    }
    return true;
}

// 判断字符串是否是带逗号
bool IsDigitWithComma(string& s) {
    if (s.empty())
        return false;
    if (s.find(",") == -1)
        return false;
    vector<string> v = SplitString(s, ",");
    if (v.empty())
        return false;
    for (int i = 1; i < v.size(); i ++) {
        if (v[i].size() != 3)
            return false;
    }
    return true;
}


// 判断字符串是否为小数
bool IsDecimal(string& s) {
    if (s.empty())
        return false;
    int temp_count = CountStr(s, '.');
    if (temp_count == 0 || temp_count > 1) return false;
    int idx = s.find('.');
    if (idx != -1) {
        string l = s.substr(0, idx);
        string r = s.substr(idx + 1);
        if ((IsDigit(l) || IsDigitWithComma(l)) && IsDigit(r))
            return true;
    }
    return false;
}

// 判断字符串是否是分数
bool IsFraction(string& s) {
    if (s.empty())
        return false;
    int temp_count = CountStr(s, '/');
    if (temp_count != 1) return false;
    int idx = s.find('/');
    if (idx != -1) {
        string l = s.substr(0, idx);
        string r = s.substr(idx + 1);
        if ((IsDigit(l) || IsDecimal(l)) && (IsDigit(r) || IsDecimal(r)))
            return true;
    }
    return false;
}
// 判断数字是否是序数
bool IsOrdinal(string& s) {
    if (s.size() < 3)
        return false;
    string tmp_r = s.substr(s.size() - 2);
    string tmp_l = s.substr(0, s.size() - 2);
//    cout << tmp_l << " " << tmp_r << endl;
    if (IsDigit(tmp_l)) {
        vector<string>::iterator it = find(ordinal.begin(), ordinal.end(), tmp_r);
        if (it != ordinal.end())
            return true;
    }
    return false;
}

bool IsPercent(string& s) {
    if (s.size() <= 1)
        return false;
    string num = s.substr(0, s.size() - 1);
    if (s[-1] == '%' && (IsDigit(num) || IsDigitWithComma(num) || IsDecimal(num)))
        return true;
    return false;

}
// 整数转字符串
string Digit2Str(int& int_temp) {
    stringstream stream;
    stream << int_temp;
    std::string string_temp;
    stream >> string_temp;
    return string_temp;
}

// 数字字符串转为整形数字
int Str2Int(string &s) {
    std::stringstream stream(s);
    int res;
    stream >> res;
    return res;
}

bool IsZero(string& s) {
    string cur_s = s;
    if (cur_s.find('.') != -1) cur_s.erase(cur_s.find('.'), 1);
    for (auto c: cur_s) {
        if (c != '0') return false;
    }
    return true;
}
// 三位的数字转为英文
string BasicConvertFunc(string& num) {
    string res = "", tmp = num;
    if (tmp == "" || tmp == " ") return "";
    while (!tmp.empty()) {
        if (tmp.size() == 3) {
            if (tmp[0] != '0')
                res += indnum[tmp[0] - '0'] + " " + units[0] + " ";
        } else if (tmp.size() == 2) {
            if (tmp[0] == '1') {
                res += indnum[Str2Int(tmp)] + " ";
                return res;
            } else if (tmp[0] != '0')
                res += decnum[tmp[0] - '2'] + " ";
        } else if (tmp.size() == 1) {
            if (tmp[0] != '0')
                res += indnum[tmp[0] - '0'] + " ";
        }
        tmp = tmp.substr(1);
    }
    return res;
}

// 将整数转换为对应的英文，目前仅能处理12位以内的数字
string ConvertInt2Eng(string& num) {
    if (IsDigitWithComma(num)) {
        vector<string> split_num = SplitString(num, ",");
        if (split_num.size() <= 1)
            return num;
        num.erase(remove(num.begin(), num.end(), ','), num.end());
    }
    if (IsDigit(num)) {
        string res = "", hundred = "", thousand = "", million = "", billion = "";
        if (num == "") return "";
        if (IsZero(num)) return "zero";
        if (num.size() > 12) {
            for (auto d: num) {
                res += indnum[d - '0'] + " ";
            }
        } else if (num.size() <= 3) {
            hundred = num;
            res += BasicConvertFunc(hundred);
        } else if (num.size() <= 6) {
            thousand = num.substr(0, num.size() - 3);
            hundred = num.substr(num.size() - 3);
            if (IsZero(thousand)) {
                res += BasicConvertFunc(hundred);
            } else
                res += BasicConvertFunc(thousand) + units[1] + " " + BasicConvertFunc(hundred);
        } else if (num.size() <= 9) {
            million = num.substr(0, num.size() - 6);
            thousand = num.substr(num.size() - 6, 3);
            hundred = num.substr(num.size() - 3);
            if (IsZero(million)) {
                res += BasicConvertFunc(thousand) + units[1] + " " + BasicConvertFunc(hundred);
            } else
                res += BasicConvertFunc(million) + units[2] + " " +
                       BasicConvertFunc(thousand) + units[1] + " " + BasicConvertFunc(hundred);
        } else {
            billion = num.substr(0, num.size() - 9);
            million = num.substr(num.size() - 9, 3);
            thousand = num.substr(num.size() - 6, 3);
            hundred = num.substr(num.size() - 3);
            if (IsZero(billion)) {
                res += BasicConvertFunc(million) + units[2] + " " +
                       BasicConvertFunc(thousand) + units[1] + " " + BasicConvertFunc(hundred);
            } else
                res += BasicConvertFunc(billion) + units[3] + " " + BasicConvertFunc(million) + units[2] + " " +
                       BasicConvertFunc(thousand) + units[1] + " " + BasicConvertFunc(hundred);
        }
        return trim(res);
    }
    return num;
}
// 将小数转为对应的英文
string ConvertDemical2Eng(string& num) {
    if (!IsDecimal(num))
        return num;
    string res = "", tmp = num;
    if (tmp.find('.') != -1) {
        vector<string> split_num = SplitString(tmp, ".");
        res += ConvertInt2Eng(split_num[0]) + " " + g_dot + " ";
        for (auto t: split_num[1]) {
            if (t == '0')
                res += "zero ";
            else
                res += indnum[t - '0'] + " ";
        }
    }
    return trim(res);
}

string ConvertOrdinal2Eng(string& s) {
    string num;
    if (IsDigit(s))
        num = s;
    else if (IsOrdinal(s))
        num = s.substr(0, s.size() - 2);
    else return s;
    string res = "";
    string num_str = ConvertInt2Eng(num);
    vector<string> split_num = SplitString(num_str, " ");
    string rep_str = ordinal_map[split_num[split_num.size() - 1]];
    for (int i = 0; i < split_num.size() - 1; i ++) {
        res += split_num[i] + " ";
    }
    res += rep_str;
    return trim(res);
}
string ConvertFraction2Eng(string& s) {
    if (!(IsFraction(s)))
        return s;
    string res = "";
    vector<string> split_num = SplitString(s, "/");
    if (split_num[1] == "0")
        res += ConvertInt2Eng(split_num[0]) + "over zero";
    else if (split_num[1] == "4") {
        if (split_num[0] == "1")
            res += "one quater";
        else
            res += ConvertInt2Eng(split_num[0]) + " " + "quaters";
    }
    else if (split_num[1] == "2") {
        if (split_num[0] == "1")
            res += "one half";
        else
            res += ConvertInt2Eng(split_num[0]) + " " + "halves";
    }
    else if (split_num[1] == "100") {
        res += ConvertInt2Eng(split_num[0]) + " " + "percent";
    }
    else if (split_num[0] == "1") {
        res += "one ";
        if (split_num[1] == "0" || split_num[1] == "1")
            res += "over " + ConvertInt2Eng(split_num[1]);
        else if (split_num[1] == "2")
            res += "half";
        else if (split_num[1] == "4")
            res += "quater";
        else
            res += ConvertOrdinal2Eng(split_num[1]);
    }
    else {
        res += ConvertInt2Eng(split_num[0]) + " " + ConvertOrdinal2Eng(split_num[1]) + "s";
    }
    return trim(res);
}

string ConvertPercent2Eng(string& s) {
    string tmp_s = s;
    if (!IsPercent(tmp_s))
        return tmp_s;
    string res = "";
    string num = tmp_s.substr(0, tmp_s.size() - 1);
    if (IsDigit(num) || IsDigitWithComma(num))
        res += ConvertInt2Eng(num);
    else if (IsDecimal(num))
        res += ConvertDemical2Eng(num);
    if (!res.empty())
        return trim(res);
    return tmp_s;
}
string ConvertNum2Eng(string& s) {
    string res = "", tmp = s;
    if (tmp[0] == '-') {
        res += g_negtive + " ";
        tmp = tmp.substr(1);
    } else if (tmp[0] == '+') {
        res += g_positive + " ";
        tmp = tmp.substr(1);
    }
    if (IsDigit(tmp) || IsDigitWithComma(tmp))
        res += ConvertInt2Eng(tmp);
    else if (IsOrdinal(tmp))
        res += ConvertOrdinal2Eng(tmp);
    else if (IsDecimal(tmp))
        res += ConvertDemical2Eng(tmp);
    else if (IsFraction(tmp))
        res += ConvertFraction2Eng(tmp);
    else if (IsPercent(tmp))
        res += ConvertPercent2Eng(tmp);
    if (res.empty())
        return s;
    else
        return trim(res);
}