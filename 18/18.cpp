#include "../lib.hpp"

int main() {
    string s;
    getline(cin, s);
    string next(s.size(), '.');
    int result = 0;
    for (int i = 0; i < 400000; i++) {
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == '.')
                result++;
            if (
                    (j > 0 && s[j-1] == '^' && s[j] == '^' && (j == s.size() - 1 || s[j+1] == '.')) ||
                    ((j == 0 || s[j-1] == '.') && s[j] == '^' && j < s.size() - 1 && s[j+1] == '^') ||
                    (j > 0 && s[j-1] == '^' && s[j] == '.' && (j == s.size() - 1 || s[j+1] == '.')) ||
                    ((j == 0 || s[j-1] == '.') && s[j] == '.' && j < s.size() - 1 && s[j+1] == '^')
               )
                next[j] = '^';
            else
                next[j] = '.';
        }
        swap(s, next);
    }
    cout << result << endl;
    return 0;
}

