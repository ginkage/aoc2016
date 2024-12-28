#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <unistd.h>
#include <Eigen/Dense>
//#include <png++/png.hpp>

using namespace std;

typedef Eigen::Vector3d vec3;
typedef Eigen::Matrix3d mat3;

static unordered_map<string, int> names;

int remap(string name) {
    auto it = names.find(name);
    if (it != names.end())
        return it->second;
    int id = names.size();
    names[name] = id;
    return id;
}

struct Hash {
    size_t operator ()(const pair<int, int>& k) const {
        return ((uint64_t)k.first << 32) + k.second;
    }
};

vector<string> split_s(const string &s, const string &delimiter) {
    vector<string> res;
    size_t pos_start = 0;
    for (size_t pos_end, delim_len = delimiter.length();
            (pos_end = s.find(delimiter, pos_start)) != string::npos;
            pos_start = pos_end + delim_len)
        res.push_back(s.substr(pos_start, pos_end - pos_start));
    res.push_back(s.substr(pos_start));
    return res;
}

vector<int> split_i(const string &s, const string &delimiter) {
    vector<int> res;
    size_t pos_start = 0;
    for (size_t pos_end, delim_len = delimiter.length();
            (pos_end = s.find(delimiter, pos_start)) != string::npos;
            pos_start = pos_end + delim_len)
        res.push_back(stoi(s.substr(pos_start, pos_end - pos_start)));
    res.push_back(stoi(s.substr(pos_start)));
    return res;
}

vector<uint64_t> split_u64(const string &s, const string &delimiter) {
    vector<uint64_t> res;
    size_t pos_start = 0;
    for (size_t pos_end, delim_len = delimiter.length();
            (pos_end = s.find(delimiter, pos_start)) != string::npos;
            pos_start = pos_end + delim_len)
        res.push_back(stoul(s.substr(pos_start, pos_end - pos_start)));
    res.push_back(stoul(s.substr(pos_start)));
    return res;
}


