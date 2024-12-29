#include "../lib.hpp"

int main() {
    int n = 3004953;
    vector<pair<int, int>> elf;
    for (int i = 1; i <= n; i++)
        elf.emplace_back(i, 1);

    while (elf.size() > 1) {
        vector<pair<int, int>> next;
        if (elf.size() % 2 != 0) {
            pair<int, int> buf { elf[0].first, elf[0].second + elf[1].second };
            for (int i = 2; i < elf.size() - 1; i += 2)
                next.emplace_back(elf[i].first, elf[i].second + elf[i + 1].second);
            next.emplace_back(elf[elf.size() - 1].first, elf[elf.size() - 1].second + buf.second);
        }
        else
            for (int i = 0; i < elf.size(); i += 2)
                next.emplace_back(elf[i].first, elf[i].second + elf[i + 1].second);
        swap(elf, next); 
    }

    cout << elf[0].first << endl;

    return 0;
}

