#include "../lib.hpp"

typedef Eigen::Vector2i vec;

vector<pair<char, vec>> dir = {
    { 'U', { -1, 0 } },
    { 'D', { 1, 0 } },
    { 'L', { 0, -1 } },
    { 'R', { 0, 1 } }
};

const regex linerex("/dev/grid/node-x(\\d+)-y(\\d+)\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)%");

struct VHash {
    size_t operator ()(const vec& k) const {
        return ((uint64_t)k[1] << 32) + k[0];
    }
};

struct node_t { int size, used; };

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

    int avail = 0;
    vector<vector<node_t>> protogrid(m, vector<node_t>(n));
    for (auto &node : nodes) {
        protogrid[node.first[0]][node.first[1]] = node.second;
        if (node.second.used == 0)
            avail = node.second.size;
    }

    vec start, goal { 0, n - 1 }, target { 0, 0 };
    vector<string> grid(m, string(n, '.'));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (protogrid[i][j].used > avail)
                grid[i][j] = '#';
            if (protogrid[i][j].used == 0)
                start = vec { i, j };
        }

    return 0;
}

