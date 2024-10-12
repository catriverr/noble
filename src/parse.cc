#pragma once

#include <string>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <map>
#include <vector>
#include <atomic>
#include <algorithm>

using std::string, std::vector, std::map;

namespace Noble {
    typedef struct {
        bool pedantic;
        string binary_name;
        vector<string> raw_args;
    } global_t;
};


#define NOBLE_PARSER_INIT
