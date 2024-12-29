#include "../lib.hpp"

typedef Eigen::Vector2i vec;

const regex linerex("/dev/grid/node-x(\\d+)-y(\\d+)\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)%");

struct VHash {
    size_t operator ()(const vec& k) const {
        return ((uint64_t)k[1] << 32) + k[0];
    }
};

struct node_t {
    int size, used;
};

int main() {
    unordered_map<vec, node_t, VHash> nodes;
    int m = 0, n = 0;

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 7) {
            int x = stoi(linematch[1].str());
            int y = stoi(linematch[2].str());
            int size = stoi(linematch[3].str());
            int used = stoi(linematch[4].str());
            nodes[vec { y, x }] = node_t { size, used };
            m = max(m, y + 1);
            n = max(n, x + 1);
        }
    }

    int result = 0;
    for (auto &a : nodes)
        for (auto &b : nodes)
            if (a.first != b.first && a.second.used > 0 && a.second.used <= (b.second.size - b.second.used))
                result++;
    cout << result << endl;

    cout << m << ' ' << n << endl;

    return 0;
}

