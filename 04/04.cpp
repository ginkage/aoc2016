#include "../lib.hpp"

int main() {
    long result = 0;
    const regex linerex("(.*)-(\\d+)\\[(.*)\\]");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 4) {
            int id = stoi(linematch[2].str());
            string crc = linematch[3].str();
            unordered_map<char, int> count;
            auto vs = split_s(linematch[1].str(), "-");
            for (string ss : vs)
                for (char c : ss)
                    count[c]--;
            set<pair<int, char>> stat;
            for (auto &it : count)
                stat.emplace(it.second, it.first);
            string cs;
            int i = 0;
            for (auto &it : stat)
                if (i++ < 5)
                    cs += it.second;
                else break;
            if (cs == crc) {
                for (string ss : vs) {
                    cout << ' ';
                    for (char c : ss)
                        cout << char('a' + (((c - 'a') + id) % 26));
                }
                cout << ' ' << id << endl;
                result += id;
            }
        }
    }
    cout << result << endl;
    return 0;
}

