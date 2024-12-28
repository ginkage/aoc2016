#include "../lib.hpp"
#include <openssl/md5.h>

int main() {
    unsigned char result[MD5_DIGEST_LENGTH];
    int len = 0, mask = 0;
    char out[9];
    out[8] = 0;
    string input = "wtnhxymk";
    for (int i = 0; i < 100000000 && (len < 8 || mask != 255); i++) {
        stringstream buf;
        buf << input << i;
        string pl = buf.str();
        MD5((const unsigned char *)pl.c_str(), pl.size(), result);
        if (result[0] == 0 && result[1] == 0 && (result[2] & 0xF0) == 0) {
            int pos = result[2];
            if (len++ < 8)
                cout << "0123456789abcdef"[pos];
            if (pos < 8 && !(mask & (1 << pos))) {
                out[pos] = "0123456789abcdef"[result[3] >> 4];
                mask |= 1 << pos;
            }
        }
    }
    cout << endl << out << endl;
    return 0;
}

