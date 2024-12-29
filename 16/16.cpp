#include "../lib.hpp"

int main() {
    string input = "11101000110010100";
    int size = 35651584;
    while (input.size() < size) {
        stringstream bs;
        for (int i = input.size() - 1; i >= 0; i--)
            bs << char('0' + (1 - (input[i] - '0')));
        input += '0' + bs.str();
    }
    string disk = input.substr(0, size);
    while (disk.size() % 2 == 0) {
        stringstream crc;
        for (int i = 0; i < disk.size(); i += 2)
            crc << char('0' + (disk[i] == disk[i+1]));
        disk = crc.str();
    }
    cout << disk << endl;
    return 0;
}

