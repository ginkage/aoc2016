#include "../lib.hpp"

struct tri { int a, b, c; };

static inline bool check(int a, int b, int c) {
    return (a + b > c && b + c > a && a + c > b);
}

int main() {
    vector<tri> v;
    const regex linerex("\\s*(\\d+)\\s+(\\d+)\\s+(\\d+)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 4) {
            int a = stoi(linematch[1].str());
            int b = stoi(linematch[2].str());
            int c = stoi(linematch[3].str());
            v.push_back(tri { a, b, c });
        }
    }

    int result = 0;
    for (int i = 0; i < v.size(); i += 3) {
        result += check(v[i+0].a, v[i+1].a, v[i+2].a);
        result += check(v[i+0].b, v[i+1].b, v[i+2].b);
        result += check(v[i+0].c, v[i+1].c, v[i+2].c);
    }
    cout << result << endl;
    return 0;
}

