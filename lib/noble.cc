#pragma once
#include <fstream>
#include <ostream>
#include <map>
#include <vector>
#include <atomic>
#include <algorithm>
#include <string>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <iostream>


#define SETUP_USINGS using std::string, std::vector, std::endl, std::cout;

SETUP_USINGS;

namespace Noble {
    namespace {
        struct version_list {
            string standard;
            string cli;
            string parser;
            string lexer;
            string tokenizer;
        };
    };
    static string version = "1.0.0";
    static version_list versions = {};
};


namespace Noble {
    typedef struct {
        bool pedantic;
        string binary_name;
        vector<string> raw_args;
    } global_t;
    global_t global;
};

void Noble_LOG(string data, char* filename, int linenumber) {
    std::cout << "[" << std::string(filename) << ":" << std::to_string(linenumber) << "] " << data;
};

#define LOG(text) Noble_LOG( text, __FILE__, __LINE__ )

#define NOBLE_INIT true


#include "standard.cc"
#include "lexer.cc"
#include "tokens.cc"
#include "parse.cc"

#define NOBLE_SOURCE_INIT true
#define NOBLE_DEFINITIVE_INIT true
