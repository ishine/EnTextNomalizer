#include "tn_util.h"

vector<string> SplitString(const string& s, const string& c)
{
    vector<string> v;
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(pos2 != -1)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
    return v;
}
// 计数指定字符出现的次数
int CountStr(const string& s, const char& c) {
    int count = 0;
    for (auto x: s) {
        if (x == c)
            count ++;
    }
    return count;
}

//去除字符串前后的空格
string trim(string& s) {
    s.erase(0, s.find_first_not_of(" \t")); // 去掉头部空格
    s.erase(s.find_last_not_of(" \t") + 1); // 去掉尾部空格
    return s;
}

wstring s2ws(const string& s) {
    string strLocale = setlocale(LC_ALL, "");
    const char* chSrc = s.c_str();
    size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
    wchar_t* wchDest = new wchar_t[nDestSize];
    wmemset(wchDest, 0, nDestSize);
    mbstowcs(wchDest, chSrc, nDestSize);
    wstring wstrResult = wchDest;
    delete[]wchDest;
    setlocale(LC_ALL, strLocale.c_str());
    return wstrResult;
}

// wstring 转换为 string
string ws2s(const wstring& ws) {
    string strLocale = setlocale(LC_ALL, "");
    const wchar_t* wchSrc = ws.c_str();
    size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
    char *chDest = new char[nDestSize];
    memset(chDest, 0, nDestSize);
    wcstombs(chDest, wchSrc, nDestSize);
    std::string strResult = chDest;
    delete[]chDest;
    setlocale(LC_ALL, strLocale.c_str());
    return strResult;
}

bool IsString(string& s) {
    for (auto c: s) {
        if (c < 'A' || c > 'z')
            return false;
        if (c > 'Z' && c < 'a')
            return false;
    }
    return true;
}
// 所有大写转小写
string Upper2Lower(string& s) {
    string res = "";
    for (auto c: s) {
        if (c >= 'A' && c <= 'Z')
            res += (c + 32);
        else
            res += c;
    }
    return res;
}
// 判断是否是纯大写单词
bool IsUpper(string& s) {
    for (auto c: s)
        if (c >= 'a' && c <= 'z')
            return false;
    return true;
}
string& strip(string &s, string c) {
    if (s.empty())
    {
        return s;
    }
    s.erase(0,s.find_first_not_of(c));
    s.erase(s.find_last_not_of(c) + 1);
    return s;
}

