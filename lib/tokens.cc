#pragma once
/// TOKENIZER FOR THE NOBLE LANGUAGE
/// (c) catriverr "github.com/catriverr" 2024
/// nehir@mybutton.org


#include <liblmf/src/strops.h>

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
    NOBLE_OPERATOR_OPEN_CURLY_BRACE, /// {
    NOBLE_OPERATOR_CLOSE_CURLY_BRACE, /// }

    NOBLE_KEYWORD_FUNCTION, /// fn
    NOBLE_KEYWORD_CLASS,    /// class  ---> Noble_Standard::TYPE
    NOBLE_KEYWORD_STRUCT,   /// struct ---> Noble_Standard::TYPE
    NOBLE_KEYWORD_RETURN,   /// return

    NOBLE_SPACING, /// space characters, ignored if not in a string.
    NOBLE_NAME,    /// name to any variable, type, function, etc
};


struct Noble_Tokenizer_Excerpt {
    Noble_Token* prev;
    Noble_Token* next;

    char character;
    Noble_Token current_token;
};

struct Noble_Tokenized_Scope {
    vector<Noble_Tokenizer_Excerpt> tokens;
    Standard_Util::ANY_SCRIPT_FILE file;
};


struct TOKENIZER_STATE {
    bool IN_STRING_LITERAL = false;
    bool IN_DEFINITION = false;
};

Noble_Tokenized_Scope tokenize_script(
    string script,
    Standard_Util::ANY_SCRIPT_FILE file = Noble_REPL
) {
    Noble_Tokenized_Scope scope;
    scope.file = file;
    scope.file.line_count = 0;
    scope.file.token_count = 0;

    /// Lines don't affect the code, since Noble does not conceptualize lines.
    /// But it's easier for reading the file in these methods.
    vector<string> lines = split_string(script, '\n');

    if (lines.size() <= 0) return scope;

    int line_number = 0;
    string* cur_line = &lines[line_number];
    while (line_number < lines.size()) {
        LOG("reading line " + std::to_string(line_number) + "\n");



        line_number++; cur_line = &lines[line_number];
    };

    return scope;
};

#define NOBLE_TOKENS_INIT true
