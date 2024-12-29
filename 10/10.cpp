#include "../lib.hpp"

int main() {
    const regex linerex1("value (.*) goes to bot (.*)");
    const regex linerex2("bot (.*) gives low to (.*) (\\d+) and high to (.*) (\\d+)");
    unordered_map<int, set<int>> input;
    unordered_map<int, set<int>> output;
    unordered_map<int, pair<int, int>> cmd;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex1) && linematch.size() == 3) {
            int val = stoi(linematch[1].str());
            int bot = stoi(linematch[2].str());
            input[bot].insert(val);
        }
        else if (regex_match(s, linematch, linerex2) && linematch.size() == 6) {
            int bot = stoi(linematch[1].str());
            string lo = linematch[2].str();
            int dlo = stoi(linematch[3].str());
            if (lo == "output")
                dlo = -1 - dlo;
            string hi = linematch[4].str();
            int dhi = stoi(linematch[5].str());
            if (hi == "output")
                dhi = -1 - dhi;
            cmd[bot] = make_pair(dlo, dhi);
        }
    }

    bool stop = false;
    while (!stop) {
        stop = true;
        for (auto &it : input)
            if (it.second.size() == 2) {
                auto &c = cmd[it.first];
                int dlo = c.first, dhi = c.second;
                int vlo = *it.second.begin(), vhi = *it.second.rbegin();
                if (vlo == 17 && vhi == 61) {
                    cout << it.first << endl;
                    // stop = true;
                }
                it.second.clear();
                if (dlo < 0) output[-1 - dlo].insert(vlo);
                else input[dlo].insert(vlo);
                if (dhi < 0) output[-1 - dhi].insert(vhi);
                else input[dhi].insert(vhi);
                stop = false;
                break;
            }
    }

    cout << *output[0].begin() * *output[1].begin() * *output[2].begin() << endl;

    return 0;
}

