#include "../lib.hpp"

long unpack(string s) {
    long result = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            stringstream d;
            for (i++; i < s.size() && s[i] != 'x'; i++)
                d << s[i];
            int span = stoi(d.str());
            stringstream t;
            for (i++; i < s.size() && s[i] != ')'; i++)
                t << s[i];
            int times = stoi(t.str());
            result += times * unpack(s.substr(i + 1, span));
            i += span;
        }
        else
            result++;
    }
    return result;
}

int main() {
    string s;
    getline(cin, s);
    cout << unpack(s) << endl;
    return 0;
}

