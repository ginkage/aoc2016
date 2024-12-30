#include "../lib.hpp"

static int di[] = { -1, 0, 1, 0 };
static int dj[] = { 0, -1, 0, 1 };

vector<string> grid;
int m, n;

union hasher_t {
    uint32_t hash;
    struct { uint8_t i, j, mask; } pos;
};

int main() {
    int si = -1, sj = -1;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        for (int j = 0; j < s.size() && sj < 0; j++)
            if (s[j] == '0') {
                si = grid.size();
                sj = j;
            }
        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();

    hasher_t h { .pos { .i = si, .j = sj, .mask = 1 } };
    unordered_map<uint32_t, int> visit;
    visit[h.hash] = 0;
    queue<uint32_t> q;
    q.push(h.hash);
    while (!q.empty()) {
        h.hash = q.front();
        q.pop();

        int steps = visit[h.hash];
        if (h.pos.mask == 0xFF && h.pos.i == si && h.pos.j == sj) {
            cout << steps << endl;
            break;
        }

        for (int k = 0; k < 4; k++) {
            hasher_t nh { .pos = { .i = h.pos.i + di[k], .j = h.pos.j + dj[k], .mask = h.pos.mask } };
            if (isdigit(grid[nh.pos.i][nh.pos.j]))
                nh.pos.mask |= (1 << (grid[nh.pos.i][nh.pos.j] - '0'));
            if (grid[nh.pos.i][nh.pos.j] != '#' && visit.find(nh.hash) == visit.end()) {
                visit[nh.hash] = steps + 1;
                q.push(nh.hash);
            }
        }
    }

    return 0;
}

