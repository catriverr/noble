#pragma once
#include "noble.cc"

SETUP_USINGS;


#define NOBLE_STANDARDIZE_LITERAL_CONTENT(x) #x /// returns x as char*
#define NOBLE_STANDARDIZE_NUMBER_CONTENT(x) std::to_string(x) /// returns (int)x as (string)x


namespace Standard_Util {
    typedef struct {
        std::string name;
        uint32_t line_count;
        uint64_t token_count;
    } ANY_SCRIPT_FILE;

    typedef struct {
        std::string filename;
        int line_number;
    } ANY_OBJECT_DEFINITION;

    typedef struct {
        std::string name;
        ANY_OBJECT_DEFINITION definition;
    } ANY_OBJECT_INFO_T;

    typedef struct {
        enum TYPE_TYPE {
            CLASS_TYPE,
            STRUCT_TYPE
        };
        TYPE_TYPE type;
    } TYPE_DEFINITION;

    using STANDARD_VALUEDEF = std::string;
};

namespace Noble_Standard {
    /// @since v1.0.0
    class Function {

    };
    /// @since v1.0.0
    struct Value {
        Standard_Util::ANY_OBJECT_DEFINITION definition;
        Standard_Util::STANDARD_VALUEDEF content;
    };

    /// @since v1.0.0
    class Type {
        std::map<string, Value> variables;
        std::map<string, Function> functions;
        std::map<Type, Value> default_cast;

        Standard_Util::ANY_OBJECT_DEFINITION definition;
        Standard_Util::TYPE_DEFINITION type_info;
    };

    /// @since v1.0.0
    class Variable {
        Type type;
        Value value;
    };
};

static Standard_Util::ANY_SCRIPT_FILE Noble_REPL = { "noble:REPL", 0, 0 };

namespace Noble_Standard_Lib {

};

class Noble_Execution_Scope {
    std::map<string, Noble_Standard::Function> functions;
    std::map<string, Noble_Standard::Variable> variables;

};

namespace Noble {
    namespace Standard = Noble_Standard;
    namespace Stdlib = Noble_Standard_Lib;
};

namespace Standard = Noble_Standard;
namespace NStdlib = Noble_Standard_Lib;

#define NOBLE_STANDARD_INIT true
