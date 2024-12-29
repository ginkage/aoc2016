#include "../lib.hpp"

int main() {
    unsigned char digest[MD5_DIGEST_LENGTH];
    string input = "ahsbgdzn";
    list<pair<int, char>> triplet;
    set<int> keys;

    for (int i = 0; i < 30000; i++) {
        stringstream buf;
        buf << input << i;
        string s = md5(buf.str());
        for (int i = 0; i < 2016; i++)
            s = md5(s);

        for (int j = 0; j < s.size() - 2; j++)
            if (s[j] == s[j+1] && s[j] == s[j+2]) {
                triplet.emplace_back(i, s[j]);
                break;
            }

        for (auto it = triplet.begin(); (it != triplet.end()) && (i - it->first > 1000); it = triplet.erase(it));

        for (auto it = triplet.begin(); it != triplet.end() && it->first < i; ) {
            char c = it->second;
            bool good = false;
            for (int j = 0; j < s.size() - 4 && !good; j++)
                for (int k = 0; k < 5 && (good || k == 0); k++)
                    good = s[j + k] == c;

            if (good) {
                keys.insert(it->first);
                it = triplet.erase(it);
            }
            else
                it++;
        }
    }

    auto it = keys.begin();
    for (int i = 1; i < 64; i++)
        it++;
    cout << *it << endl;

    return 0;
}

