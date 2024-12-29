#include "../lib.hpp"

int main() {
    int n = 3004953;
    list<int> elf;
    for (int i = 1; i <= n; i++)
        elf.emplace_back(i);

    auto it = elf.begin(), jt = it;
    for (int i = 0; i < elf.size() / 2; i++)
        jt++;

    while (elf.size() > 1) {
        auto kt = jt;

        jt++;
        if (jt == elf.end())
            jt = elf.begin();

        elf.erase(kt);

        if (elf.size() % 2 == 0) {
            jt++;
            if (jt == elf.end())
                jt = elf.begin();
        }

        it++;
        if (it == elf.end())
            it = elf.begin();
    }

    cout << *it << endl;

    return 0;
}

