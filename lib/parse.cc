#pragma once
#include "noble.cc"

#define NOBLE_PARSER_VERSION "1.0.0"

int set_version_P() {
    Noble::versions.parser = NOBLE_PARSER_VERSION;
    return 0;
};

static int setter_P = (int)set_version_P();

namespace Noble {
    namespace Parser {
        
    };
};

#define NOBLE_PARSER_INIT true
