#include "../lib.hpp"

int main() {
    int m = 6, n = 50;
    vector<string> grid(m, string(n, '.'));
    const regex linerex1("rect (.*)x(.*)");
    const regex linerex2("rotate (.*)=(.*) by (.*)");
    string cb(m, '.'), rb(n, '.');
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex1) && linematch.size() == 3) {
            int x = stoi(linematch[1].str());
            int y = stoi(linematch[2].str());
            for (int i = 0; i < y; i++)
                for (int j = 0; j < x; j++)
                    grid[i][j] = '#';
        }
        else if (regex_match(s, linematch, linerex2) && linematch.size() == 4) {
            bool col = linematch[1].str() != "row y";
            int coord = stoi(linematch[2].str());
            int shift = stoi(linematch[3].str());
            if (col) {
                for (int i = 0; i < m; i++)
                    cb[(i + shift) % m] = grid[i][coord];
                for (int i = 0; i < m; i++)
                    grid[i][coord] = cb[i];
            }
            else {
                for (int j = 0; j < n; j++)
                    rb[(j + shift) % n] = grid[coord][j];
                for (int j = 0; j < n; j++)
                    grid[coord][j] = rb[j];
            }
        }
    }

    int result = 0;
    for (string s : grid) {
        cout << s << endl;
        for (char c : s)
            if (c == '#')
                result++;
    }
    cout << result << endl;

    return 0;
}

