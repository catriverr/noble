#pragma once
/// TOKENIZER FOR THE NOBLE LANGUAGE
/// (c) catriverr "github.com/catriverr" 2024
/// nehir@mybutton.org


#include <cstring>
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
    NOBLE_NOT_SET,            /// UNSET, start of the script for example.


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
    NOBLE_OPERATOR_DOUBLECOLON,
    NOBLE_OPERATOR_OPEN_CURLY_BRACE, /// {
    NOBLE_OPERATOR_CLOSE_CURLY_BRACE, /// }
    NOBLE_OPERATOR_DOT,               /// .
    NOBLE_OPERATOR_OPEN_PARANTHESES, /// (
    NOBLE_OPERATOR_CLOSE_PARANTHESES, /// )
    NOBLE_OPERATOR_GREATER_THAN, /// >
    NOBLE_OPERATOR_LESS_THAN, /// <
    NOBLE_OPERATOR_OPEN_BLOCK_BRACE, /// [
    NOBLE_OPERATOR_CLOSE_BLOCK_BRACE, /// ]
    NOBLE_OPERATOR_COMMA, /// ,
    NOBLE_OPERATOR_AND, /// &
    NOBLE_OPERATOR_POUND, /// #
    NOBLE_OPERATOR_AT, /// @
    NOBLE_OPERATOR_EXCLAMATION, /// !

    NOBLE_KEYWORD_FUNCTION, /// fn
    NOBLE_KEYWORD_CLASS,    /// class  ---> Noble_Standard::TYPE
    NOBLE_KEYWORD_STRUCT,   /// struct ---> Noble_Standard::TYPE
    NOBLE_KEYWORD_RETURN,   /// return
    NOBLE_KEYWORD_IF, /// if
    NOBLE_KEYWORD_FOR, /// for
    NOBLE_KEYWORD_WHILE, /// while
    NOBLE_KEYWORD_SWITCH, /// switch

    NOBLE_SPACING, /// space characters, ignored if not in a string.
    NOBLE_NAME,    /// name to any variable, type, function, etc
    NOBLE_TEXT, /// any text, unrecognized tokens
    NOBLE_EOF, /// end of file token
};


struct Noble_Tokenizer_Excerpt {
    Noble_Token* prev;

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

void rplc_substr(std::string &str, const std::string &subStr, char dest) {
    size_t pos = 0;
    // Loop to find all occurrences of subStr and replace them with dest
    while ((pos = str.find(subStr, pos)) != std::string::npos) {
        // Replace subStr with the character dest
        str.replace(pos, subStr.length(), 1, dest); // Create a string of length 1 with dest
        pos += 1; // Move past the newly inserted character
    }
}

#define tstr(x) (char)x


static std::map<string, char> NOBLE_KEYWORD_REPLACEMENT_MATCH_TABLE = {
    { "class", 0xFF },   { "struct", 0xFF },
    { "fn", 0xFF2 },     { "function", 0xFF2 },
    { "return", 0xFF3 }, { "ret", 0xFF3 }
};

void NOBLE_REPLACE_KEYWORDS( string* str ) {
    for (auto entry : NOBLE_KEYWORD_REPLACEMENT_MATCH_TABLE) {
        std::cout << entry.first << " | [" << entry.second << "] (: " << std::to_string((unsigned int)entry.second) << ")" << '\n';
        rplc_substr(*str, entry.first, entry.second); /// entry.first = keyword, entry.second = charcode
    };
};

Noble_Tokenized_Scope tokenize_script(
    string script,
    Standard_Util::ANY_SCRIPT_FILE file = Noble_REPL
) {
    Noble_Tokenized_Scope scope;
    TOKENIZER_STATE state;

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
   ///
        NOBLE_REPLACE_KEYWORDS( cur_line );
   ///  c strings are so old, man.
        char* medieval_string = (char*)cur_line;
        for (int i = 0; i < strlen(medieval_string); i++) {
            char cur_char = medieval_string[i];
            Noble_Token* PREV_TOKEN = i > 0 ? &scope.tokens[0].current_token : nullptr;

#define push_token(x,y) scope.tokens.push_back({ PREV_TOKEN, x, y })
#define NOSTRINGONLY() if (state.IN_STRING_LITERAL) break
#define IF_STRING() if (state.IN_STRING_LITERAL)

    /// I'm stuck here.
    /// Tokenization can be completed but it's a worthless task,
    /// as the actual hassle is in the parser.
    /// Which I'm not sure how I will implement.
    /// It requires a lot of state variables, mainly booleans
    /// for stuff like arithmetics
    ///
    /// I'm thinking of not doing arithmetics at the start of this
    /// otherwise I can never get to actual function definitions



            switch (cur_char) {
                /// ALL SPACE CHARACTERS
                /// (SOME CHARACTERS MAY NOT BE RECOGNIZED)
                /// SET AS NOBLE_SPACING
                case ' ': case '\t':
                case '\r': case '\n':
                    IF_STRING() push_token(cur_char, NOBLE_FRAGMENT_CHARACTER);
                    NOSTRINGONLY();
                    push_token(cur_char, NOBLE_SPACING);
                    break;

                case ':':
                    IF_STRING() push_token(cur_char, NOBLE_FRAGMENT_CHARACTER);
                    NOSTRINGONLY();
                    push_token( cur_char, NOBLE_OPERATOR_COLON );
                    break;

                case '.':
                    IF_STRING() push_token(cur_char, NOBLE_FRAGMENT_CHARACTER);
                    NOSTRINGONLY();
                    push_token(cur_char, NOBLE_OPERATOR_DOT);
                    break;

                case '0': case '1': case '2': case '3':
                case '4': case '5': case '6': case '7':
                case '8': case '9':
                    IF_STRING() push_token(cur_char, NOBLE_FRAGMENT_CHARACTER);
                    NOSTRINGONLY();
                    break;

                default:
                    if (state.IN_STRING_LITERAL) push_token(cur_char,NOBLE_FRAGMENT_CHARACTER);
                    else push_token(cur_char, NOBLE_TEXT);
                    break;
            };
            scope.file.token_count++;
        };
        scope.file.line_count++;
        line_number++; cur_line = &lines[line_number];
    };

    return scope;
};

#define NOBLE_TOKENS_INIT true
