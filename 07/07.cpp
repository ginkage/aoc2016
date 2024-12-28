#include "../lib.hpp"

bool abba(string &s) {
    for (int i = 0; i < s.size() - 3; i++)
        if (s[i] != s[i + 1] && s[i] == s[i + 3] && s[i + 1] == s[i + 2])
            return true;
    return false;
}

bool check_abba(string &s) {
    bool abba_out = false, abba_in = false;
    auto vs = split_s(s, "]");
    for (string os : vs) {
        auto ws = split_s(os, "[");
        abba_out |= abba(ws[0]);
        if (ws.size() > 1)
            abba_in |= abba(ws[1]);
    }
    return abba_out && !abba_in;
}

vector<string> aba(string &s, bool in) {
    vector<string> res;
    for (int i = 0; i < s.size() - 2; i++)
        if (s[i] != s[i + 1] && s[i] == s[i + 2]) {
            string r = s.substr(i, 3);
            if (in) {
                r[0] = r[1];
                r[1] = r[2];
                r[2] = r[0];
            }
            res.push_back(r);
        }
    return res;
}

bool check_aba(string &s) {
    vector<string> aba_out, aba_in;
    auto vs = split_s(s, "]");
    for (string os : vs) {
        auto ws = split_s(os, "[");
        for (string &out : aba(ws[0], false))
            aba_out.push_back(out);
        if (ws.size() > 1)
            for (string &in : aba(ws[1], true))
                aba_in.push_back(in);
    }
    for (string &out : aba_out)
        for (string &in : aba_in)
            if (in == out)
                return true;
    return false;
}

int main() {
    int result_a = 0, result_b = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        result_a += check_abba(s);
        result_b += check_aba(s);
    }
    cout << result_a << ' ' << result_b << endl;
    return 0;
}

