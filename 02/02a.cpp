#include "../lib.hpp"

typedef Eigen::Vector2i vec;

unordered_map<char, vec> dir = {
    { 'U', { 0, -1 } },
    { 'L', { -1, 0 } },
    { 'D', { 0, 1 } },
    { 'R', { 1, 0 } }
};

vector<string> keypad = {
    "123",
    "456",
    "789"
};

int main() {
    vec pos { 1, 1 };
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        for (char c : s) {
            pos += dir[c];
            pos[0] = min(max(0, pos[0]), 2);
            pos[1] = min(max(0, pos[1]), 2);
        }
        cout << keypad[pos[1]][pos[0]];
    }
    cout << endl;

    return 0;
}

