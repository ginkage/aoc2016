#include "../lib.hpp"

typedef Eigen::Vector2i vec;

vector<pair<char, vec>> dir = {
    { 'U', { -1, 0 } },
    { 'D', { 1, 0 } },
    { 'L', { 0, -1 } },
    { 'R', { 0, 1 } }
};

int main() {
    string input = "dmypynyp";
    queue<pair<vec, string>> q;
    q.emplace(vec { 0, 0 }, "");
    bool done = false;
    size_t result = 0;
    while (!q.empty()) {
        auto it = q.front();
        q.pop();

        if (it.first[0] == 3 && it.first[1] == 3) {
            if (result == 0)
                cout << it.second << endl;
            result = max(result, it.second.size());
        }
        else {
            string h = md5(input + it.second);
            for (int i = 0; i < 4; i++) {
                vec np = it.first + dir[i].second;
                if (np[0] >= 0 && np[1] >= 0 && np[0] < 4 && np[1] < 4 && h[i] > 'a')
                    q.emplace(np, it.second + dir[i].first);
            }
        }
    }
    cout << result << endl;
    return 0;
}

