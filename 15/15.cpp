#include "../lib.hpp"

struct disc_t { int d, np, p0; };

int main() {
    vector<disc_t> disc;
    const regex linerex("Disc #(.*) has (.*) positions; at time=0, it is at position (.*).");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 4)
            disc.push_back(disc_t {
                stoi(linematch[1].str()),
                stoi(linematch[2].str()),
                stoi(linematch[3].str()) });
    }

    disc.push_back(disc_t { disc.size() + 1, 11, 0 });

    for (int t = 0; t < 5000000; t++) {
        int count = 0;
        for (disc_t &d : disc)
            if ((d.d + d.p0 + t) % d.np == 0)
                count++;
        if (count == disc.size())
            cout << t << endl;
    }

    return 0;
}

