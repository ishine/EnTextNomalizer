#include "tn_signal.h"
#include "tn_number.h"
map<string, string> ruler_map = {
        {"um", "micron"},
        {"mm", "millimeter"},
        {"cm", "centimeter"},
        {"dm", "decimeter"},
        {"m", "meter"},
        {"km", "kilometer"},
        {"um²", "square micron"},
        {"um2", "square micron"},
        {"mm²", "square millimeter"},
        {"mm2", "square millimeter"},
        {"cm²", "square centimeter"},
        {"cm2", "square centimeter"},
        {"dm²", "square decimeter"},
        {"dm2", "square decimeter"},
        {"m²", "square meter"},
        {"m2", "square meter"},
        {"km²", "square kilometer"},
        {"km2", "square kilometer"},
        {"um³", "cubic micron"},
        {"um3", "cubic micron"},
        {"mm³", "cubic millimeter"},
        {"mm3", "cubic millimeter"},
        {"cm³", "cubic centimeter"},
        {"cm3", "cubic centimeter"},
        {"dm³", "cubic decimeter"},
        {"dm3", "cubic decimeter"},
        {"m³", "cubic meter"},
        {"m3", "cubic meter"},
        {"km³", "cubic kilometer"},
        {"km3", "cubic kilometer"},
        {"mL", "milliliter"},
        {"L", "liter"},
        {"ug", "microgram"},
        {"mg", "milligram"},
        {"g", "gram"},
        {"kg", "kilogram"},
        {"t", "ton"},
        {"d", "day"},
        {"h", "hour"},
        {"min", "minute"},
        {"s", "second"},
        {"ft", "feet"},
        {"k", "kelvin"},
        {"mol", "mole"},
        {"cd", "candela"},
        {"rad", "radian"},
        {"sr", "steradian"},
        {"ha", "hectare"},
        {"atm", "standard atmosphere"},
};

map<wstring, string> punc_map = {
        {L"&", "and"},
        {L"+", "plus"},
        {L"@", "at"},
        {L"=", "equals"},
        {L"°", "degree"},
        {L"℃", "degree"},
        {L"%", "percent"},


};

// basic constant
map<wstring, string> greek = {
        {L"α", "alpha"},
        {L"β", "beta"},
        {L"γ", "gamma"},
        {L"Γ", "gamma"},
        {L"Δ", "delta"},
        {L"δ", "delta"},
        {L"ε", "epsilon"},
        {L"ζ", "zeta"},
        {L"η", "ita"},
        {L"θ", "theta"},
        {L"ι", "iota"},
        {L"κ", "kappa"},
        {L"λ", "lamda"},
        {L"∧", "lamda"},
        {L"μ", "mu"},
        {L"ν", "nu"},
        {L"ξ", "xi"},
        {L"Ξ", "xi"},
        {L"π", "pi"},
        {L"∏", "pi"},
        {L"ρ", "rho"},
        {L"σ", "sigma"},
        {L"∑", "sigma"},
        {L"τ", "tau"},
        {L"υ", "upsilon"},
        {L"φ", "phi"},
        {L"Φ", "phi"},
        {L"χ", "chi"},
        {L"ψ", "psi"},
        {L"ω", "omega"},
        {L"Ω", "omega"},
};
vector<string> puncs = {".", ",", "!", "\"", "(", ")", ";", "<", "\'",
                        ">", "?", "[", "]", "{", "}", "~", ":", "-"};

// 判断是否为希腊字母
bool IsGreek(wstring& s) {
    map<wstring, string>::iterator it = greek.find(s);
    return it != greek.end();
}

// 将希腊字母转为对应的英文
string ProcessGreek(string& text) {
    string res = "";
    wstring new_text = s2ws(text);
    for (int i = 0; i < new_text.size(); i ++) {
        wstring cur_s = new_text.substr(i, 1);
//        cout << cur_s << endl;
        if (IsGreek(cur_s))
            res += " " + greek[cur_s] + " ";
        else res += ws2s(cur_s);
    }
    return trim(res);
}

// 单位的正则有三种：
// 1：123km，数字与单位相连
// 2：123 km，数字与单位之间有空格
// 3：one km，数字单词与单位之间有空格
string SplitRuler(string& s) {
    if (s.size() <= 1) return s;
    string res = "";
    for (int i = s.size() - 1; i > 0; i --) {
        string l = s.substr(0, i);
        string r = s.substr(i);
        map<string, string>::iterator it = ruler_map.find(r);
        if ((IsDigit(l) || IsDigitWithComma(l) || IsDecimal(s)) && it != ruler_map.end()) {
            res += l + " " + r;
            return res;
        }
    }
    return s;
}
bool IsRuler(string& s) {
    map<string, string>::iterator it = ruler_map.find(s);
    if (it != ruler_map.end())
        return true;
    return false;

}

// 目前仅仅是将单位转为对应的英文读法，未考虑单复数的问题
string Ruler2Eng(string& s) {
    string res = "";
    map<string, string>::iterator it = ruler_map.find(s);
    if (it != ruler_map.end()) {
        res += ruler_map[s];
        return res;
    }
    return s;
}

// 将部分符号转为对应的读法
string Signal2Eng(string &s) {
    if (s.empty())
        return "";
    string res = "";
    for (int i = 0; i < s.size(); i ++) {
        map<wstring, string>::iterator it = punc_map.find(s2ws(s.substr(i, 1)));
        if (it != punc_map.end())
             res += " " + punc_map[s2ws(s.substr(i, 1))] + " ";
        else
            res += s[i];
    }
    if (!res.empty())
        return trim(res);
    else
        return s;
}

string RemovePuncs(string& s) {
    string tmp_s = s;
    while (tmp_s.size() > 0 && (find(puncs.begin(), puncs.end(), tmp_s.substr(tmp_s.size() - 1)) != puncs.end())) {
        tmp_s.erase(tmp_s.size() - 1);
    }
    while (tmp_s.size() > 0 && (find(puncs.begin(), puncs.end(), tmp_s.substr(0, 1)) != puncs.end())) {
        tmp_s.erase(0);
    }
    return tmp_s;
}