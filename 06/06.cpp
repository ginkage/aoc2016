#include "../lib.hpp"

int main() {
    unordered_map<int, unordered_map<char, int>> stats;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        for (int i = 0; i < s.size(); i++)
            stats[i][s[i]]++;
    }

    unordered_map<int, set<pair<int, char>>> restats;
    for (auto it : stats)
        for (auto jt : it.second)
            restats[it.first].emplace(jt.second, jt.first);

    for (int i = 0; i < stats.size(); i++)
        cout << restats[i].begin()->second;
    cout << endl;

    return 0;
}

