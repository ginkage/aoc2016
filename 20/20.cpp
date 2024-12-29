#include "../lib.hpp"

int main() {
    uint64_t result = 0;
    set<pair<uint64_t, uint64_t>> ranges;
    const regex linerex("(.*)-(.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            uint64_t start = stoll(linematch[1].str());
            uint64_t end = stoll(linematch[2].str());
            ranges.emplace(start, end);
        }
    }

    for (auto it : ranges)
        if (result >= it.first && result <= it.second)
            result = it.second + 1;
    cout << result << endl;

    uint64_t vacant = 0;
    pair<uint64_t, uint64_t> prev(0, 0);
    vector<pair<uint64_t, uint64_t>> isect;
    for (auto it : ranges) {
        if (prev.first <= it.second && it.first <= prev.second)
            prev = make_pair(min(it.first, prev.first), max(it.second, prev.second));
        else {
            vacant += (it.first - prev.second - 1);
            prev = it;
        }
    }
    cout << vacant << endl;

    return 0;
}

