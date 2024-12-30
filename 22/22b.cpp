#include "../lib.hpp"

typedef Eigen::Vector2i vec;

vector<vec> dir = {
    { -1, 0 },
    { 1, 0 },
    { 0, -1 },
    { 0, 1 }
};

const regex linerex("/dev/grid/node-x(\\d+)-y(\\d+)\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)%");

struct VHash {
    size_t operator ()(const vec& k) const {
        return ((uint64_t)k[1] << 32) + k[0];
    }
};

struct node_t { int size, used; };

union hasher_t {
    uint32_t hash;
    struct { int8_t i, j, gi, gj; } pos;
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

    int avail = 0;
    vector<vector<node_t>> protogrid(m, vector<node_t>(n));
    for (auto &node : nodes) {
        protogrid[node.first[0]][node.first[1]] = node.second;
        if (node.second.used == 0)
            avail = node.second.size;
    }

    vec start;
    vector<string> grid(m, string(n, '.'));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (protogrid[i][j].used > avail)
                grid[i][j] = '#';
            if (protogrid[i][j].used == 0)
                start = vec { i, j };
        }

    hasher_t sth = { .pos = { .i = start[0], .j = start[1], .gi = 0, .gj = n - 1 } };
    unordered_map<uint32_t, uint32_t> visit;
    visit[sth.hash] = 0;
    queue<uint32_t> q;
    q.push(sth.hash);
    while (!q.empty()) {
        hasher_t h = { .hash = q.front() };
        q.pop();

        int steps = visit[h.hash];
        vec pos { h.pos.i, h.pos.j }, goal { h.pos.gi, h.pos.gj };
        if (goal[0] == 0 && goal[1] == 0) {
            cout << steps << endl;
            break;
        }

        for (int i = 0; i < 4; i++) {
            vec np = pos + dir[i];
            if (np[0] >= 0 && np[1] >= 0 && np[0] < m && np[1] < n && grid[np[0]][np[1]] != '#') {
                hasher_t ns;
                if (np == goal)
                    ns = { .pos = { .i = np[0], .j = np[1], .gi = pos[0], .gj = pos[1] } };
                else
                    ns = { .pos = { .i = np[0], .j = np[1], .gi = goal[0], .gj = goal[1] } };
                if (visit.find(ns.hash) == visit.end()) {
                    visit[ns.hash] = steps + 1;
                    q.push(ns.hash);
                }
            }
        }
    }

    return 0;
}

