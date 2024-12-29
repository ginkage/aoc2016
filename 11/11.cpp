#include "../lib.hpp"

//       0     1     2     3     4
// F4 .  .  .  .  .  .  .  .  .  .  .
// F3 .  .  .  .  .  .  TM .  .  .  .
// F2 .  .  .  .  .  TG .  RG RM CG CM
// F1 E  SG SM PG PM .  .  .  .  .  .
//    0  2  4  6  8  10 12 14 16 18 20

static const int parts = 7;

static inline int get_at(uint32_t state, int bit) {
    return (state >> bit) & 3;
}

static inline uint32_t set_at(uint32_t state, int bit, int val) {
    return (state & ~(3 << bit)) | (val << bit);
}

static inline int gen(int g) {
    return g * 4 + 2;
}

static inline int chip(int c) {
    return c * 4 + 4;
}

static inline int get_floor(uint32_t state) {
    return get_at(state, 0);
}

static inline int get_gen(uint32_t state, int g) {
    return get_at(state, gen(g));
}

static inline int get_chip(uint32_t state, int c) {
    return get_at(state, chip(c));
}

static inline uint32_t set_floor(uint32_t state, int val) {
    return set_at(state, 0, val);
}

static inline uint32_t set_gen(uint32_t state, int g, int val) {
    return set_at(state, gen(g), val);
}

static inline uint32_t set_chip(uint32_t state, int c, int val) {
    return set_at(state, chip(c), val);
}

bool is_valid(uint32_t s) {
    for (int i = 0; i < parts; i++) {
        int fi = get_chip(s, i);
        if (fi != get_gen(s, i))
            for (int j = 0; j < parts; j++)
                if (i != j && fi == get_gen(s, j))
                    return false;
    }
    return true;
}

bool is_end(uint32_t s) {
    for (int i = 0; i < parts; i++)
        if (get_chip(s, i) != 3 || get_gen(s, i) != 3)
            return false;
    return true;
}

unordered_set<uint32_t> new_states(uint32_t s) {
    unordered_set<uint32_t> result;
    int myfloor = get_floor(s);
    for (int nf = myfloor - 1; nf <= myfloor + 1; nf++)
        if (nf >= 0 && nf < 4 && nf != myfloor) {
            uint32_t ms = set_floor(s, nf);
            for (int i = 0; i < parts; i++) {
                if (get_chip(s, i) == myfloor) {
                    uint32_t ns = set_chip(ms, i, nf);
                    if (is_valid(ns)) result.insert(ns);
                    if (get_gen(s, i) == myfloor) {
                        uint32_t nns = set_gen(ns, i, nf);
                        if (is_valid(nns)) result.insert(nns);
                    }
                    for (int j = i + 1; j < parts; j++) {
                        if (get_chip(s, j) == myfloor) {
                            uint32_t nns = set_chip(ns, j, nf);
                            if (is_valid(nns)) result.insert(nns);
                        }
                        if (get_gen(s, j) == myfloor) {
                            uint32_t nns = set_gen(ns, j, nf);
                            if (is_valid(nns)) result.insert(nns);
                        }
                    }
                }
                if (get_gen(s, i) == myfloor) {
                    uint32_t ns = set_gen(ms, i, nf);
                    if (is_valid(ns)) result.insert(ns);
                    for (int j = i + 1; j < parts; j++) {
                        if (get_chip(s, j) == myfloor) {
                            uint32_t nns = set_chip(ns, j, nf);
                            if (is_valid(nns)) result.insert(nns);
                        }
                        if (get_gen(s, j) == myfloor) {
                            uint32_t nns = set_gen(ns, j, nf);
                            if (is_valid(nns)) result.insert(nns);
                        }
                    }
                }
            }
        }
    return result;
}

void print(uint32_t state) {
    for (int f = 3; f >= 0 ; f--) {
        cout << ((get_floor(state) == f) ? " E " : " . ");
        for (int i = 0; i < parts; i++) {
            if (get_gen(state, i) == f) cout << " G" << i;
            else cout << " . ";
            if (get_chip(state, i) == f) cout << " M" << i;
            else cout << " . ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    uint32_t state = 0;

    state = set_floor(state, 0);
    state = set_gen(state, 0, 0);
    state = set_chip(state, 0, 0);
    state = set_gen(state, 1, 0);
    state = set_chip(state, 1, 0);
    state = set_gen(state, 2, 1);
    state = set_chip(state, 2, 2);
    state = set_gen(state, 3, 1);
    state = set_chip(state, 3, 1);
    state = set_gen(state, 4, 1);
    state = set_chip(state, 4, 1);
    state = set_gen(state, 5, 0);
    state = set_chip(state, 5, 0);
    state = set_gen(state, 6, 0);
    state = set_chip(state, 6, 0);
/*
    state = set_floor(state, 0);
    state = set_gen(state, 0, 1);
    state = set_chip(state, 0, 0);
    state = set_gen(state, 1, 2);
    state = set_chip(state, 1, 0);
*/
    print(state);

    queue<uint32_t> q;
    unordered_map<uint32_t, int> visit;
    //unordered_map<uint32_t, uint32_t> prev;
    q.push(state);
    visit[state] = 0;
    while (!q.empty()) {
        state = q.front();
        q.pop();

        int steps = visit[state];
        if (is_end(state)) {
            cout << steps << endl;
            print(state);
            //for (auto it = prev.find(state); it != prev.end(); it = prev.find(it->second))
            //    print(it->second);
            break;
        }

        for (uint32_t s : new_states(state))
            if (visit.find(s) == visit.end()) {
                visit[s] = steps + 1;
                q.push(s);
                //prev[s] = state;
            }
    }

    return 0;
}

