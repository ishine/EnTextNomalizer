#include "tn_cases.h"
std::string Mail2Eng(string &s) {
    if (s.size() <= 4)
        return s;
    string prefix_4 = s.substr(0, 4);
    string res = "";
    string tmp_s = s;
    if (Upper2Lower(prefix_4) == "http" || Upper2Lower(prefix_4) == "www.") {
        for (int i = 0; i < tmp_s.size(); i ++) {
            if (tmp_s[i] == ':')
                res += "colon ";
            else if (tmp_s[i] == '.')
                res += "dot ";
            else if (tmp_s[i] == '/')
                res += "slash ";
            else
                res += tmp_s.substr(i, 1) + " ";
        }
    }
    if (res.empty())
        return s;
    return trim(res);
}