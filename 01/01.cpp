#include "../lib.hpp"

int main() {
    int i = 0, j = 0, di = -1, dj = 0;
    string s;
    getline(cin, s);
    unordered_set<pair<int, int>, Hash> visit;
    for (string d : split_s(s, ", ")) {
        char dir = d[0];
        int len = stoi(d.substr(1, d.size() - 1));
        if (dir == 'R') {
            int tmp = dj;
            dj = -di;
            di = tmp;
        }
        else {
            int tmp = dj;
            dj = di;
            di = -tmp;
        }

        for (int t = 0; t < len; t++) {
            i += di;
            j += dj;
            if (visit.find(make_pair(i, j)) != visit.end())
                cout << abs(i) + abs(j) << endl;
            visit.emplace(i, j);
        }
    }
    cout << abs(i) + abs(j) << endl;

    return 0;
}

