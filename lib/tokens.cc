#pragma once
#include "noble.cc"

SETUP_USINGS;

#define NOBLE_TOKENS_VERSION "1.0.0"

int set_version_T() {
    Noble::versions.parser = NOBLE_TOKENS_VERSION;
    return 0;
};

static int setter_T = (int)set_version_T();

enum Noble_Token {
    NOBLE_FRAGMENT_NUMBER,    /// 0..9
    NOBLE_FRAGMENT_CHARACTER, /// abc..xyz

    NOBLE_LITERAL_STRING_START, /// '..
    NOBLE_LITERAL_STRING_END,   ///  ..'

    NOBLE_OPERATOR_MINUS,/// -
    NOBLE_OPERATOR_PLUS, /// +
    NOBLE_OPERATOR_MULT, /// *
    NOBLE_OPERATOR_DIVISION, /// /
    NOBLE_OPERATOR_SEMICOLON, /// ;
    NOBLE_OPERATOR_COLON,   /// : // i forgot the name of this

    NOBLE_KEYWORD_FUNCTION, /// fn
    NOBLE_KEYWORD_CLASS,    /// class  ---> Noble_Standard::TYPE
    NOBLE_KEYWORD_STRUCT,   /// struct ---> Noble_Standard::TYPE
    NOBLE_KEYWORD_RETURN,   /// return
};


struct Noble_Tokenizer_Scope {
    Noble_Token* prev;
    Noble_Token* next;

    char character;
    Noble_Token current_token;
};

#define NOBLE_TOKENS_INIT true
