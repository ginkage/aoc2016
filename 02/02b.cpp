#include "../lib.hpp"

typedef Eigen::Vector2i vec;

unordered_map<char, vec> dir = {
    { 'U', { -1, 0 } },
    { 'L', { 0, -1 } },
    { 'D', { 1, 0 } },
    { 'R', { 0, 1 } }
};

vector<string> keypad = {
    "  1",
    " 234",
    "56789",
    " ABC",
    "  D"
};

int main() {
    vec pos { 2, 0 };
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        for (char c : s) {
            vec np = pos + dir[c];
            if (np[0] >= 0 && np[1] >= 0
                    && np[0] < keypad.size() && np[1] < keypad[np[0]].size()
                    && keypad[np[0]][np[1]] != ' ')
                pos = np;
        }
        cout << keypad[pos[0]][pos[1]];
    }
    cout << endl;

    return 0;
}

