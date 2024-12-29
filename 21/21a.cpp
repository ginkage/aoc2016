#include "../lib.hpp"

const regex linerex1("swap position (.*) with position (.*)");
const regex linerex2("swap letter (.*) with letter (.*)");
const regex linerex3("rotate left (.*) steps*");
const regex linerex4("rotate right (.*) steps*");
const regex linerex5("rotate based on position of letter (.*)");
const regex linerex6("reverse positions (.*) through (.*)");
const regex linerex7("move position (.*) to position (.*)");

int main() {
    string str = "abcdefgh";
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex1) && linematch.size() == 3) {
            // Swap position X with position Y
            // letters at indexes X and Y (counting from 0) should be swapped.
            int x = stoi(linematch[1].str());
            int y = stoi(linematch[2].str());
            swap(str[x], str[y]);
        }
        else if (regex_match(s, linematch, linerex2) && linematch.size() == 3) {
            // Swap letter X with letter Y
            // letters X and Y should be swapped (regardless of where they appear in the string).
            char x = linematch[1].str()[0];
            char y = linematch[2].str()[0];
            for (char &c : str)
                if (c == x)
                    c = y;
                else if (c == y)
                    c = x;
        }
        else if (regex_match(s, linematch, linerex3) && linematch.size() == 2) {
            // Rotate left X steps
            // whole string should be rotated; for example, one right rotation would turn abcd into dabc.
            int x = stoi(linematch[1].str());

            string ns(str.size(), ' ');
            for (int i = 0; i < str.size(); i++)
                ns[(i + str.size() - x) % str.size()] = str[i];
            swap(str, ns);
        }
        else if (regex_match(s, linematch, linerex4) && linematch.size() == 2) {
            // Rotate right X steps
            // whole string should be rotated; for example, one right rotation would turn abcd into dabc.
            int x = stoi(linematch[1].str());

            string ns(str.size(), ' ');
            for (int i = 0; i < str.size(); i++)
                ns[(i + x) % str.size()] = str[i];
            swap(str, ns);
        }
        else if (regex_match(s, linematch, linerex5) && linematch.size() == 2) {
            // Rotate based on position of letter X
            // whole string should be rotated to the right based on the index of letter X (counting from 0)
            // as determined before this instruction does any rotations. Once the index is determined,
            // rotate the string to the right one time, plus a number of times equal to that index,
            // plus one additional time if the index was at least 4.
            char x = linematch[1].str()[0];
            int pos = str.find(x);
            if (pos >= 4)
                pos++;
            pos++;

            string ns(str.size(), ' ');
            for (int i = 0; i < str.size(); i++)
                ns[(i + pos) % str.size()] = str[i];
            swap(str, ns);
        }
        else if (regex_match(s, linematch, linerex6) && linematch.size() == 3) {
            // Reverse positions X through Y
            // span of letters at indexes X through Y (including the letters at X and Y) should be reversed in order.
            int x = stoi(linematch[1].str());
            int y = stoi(linematch[2].str());
            while (x < y)
                swap(str[x++], str[y--]);
        }
        else if (regex_match(s, linematch, linerex7) && linematch.size() == 3) {
            // Move position X to position Y
            // letter which is at index X should be removed from the string, then inserted such that it ends up at index Y.
            int x = stoi(linematch[1].str());
            int y = stoi(linematch[2].str());
            char c = str[x];
            str.erase(str.begin() + x);
            str.insert(str.begin() + y, c);
        }
    }
    cout << str << endl;
    return 0;
}

