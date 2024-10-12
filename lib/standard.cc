#pragma once
#include "noble.cc"

SETUP_USINGS;

namespace Standard_Util {

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
};

namespace Noble_Standard {
    /// @since v1.0.0
    class Function {

    };
    /// @since v1.0.0
    struct Value {
        Standard_Util::ANY_OBJECT_DEFINITION definition;
        
    };

    /// @since v1.0.0
    class Type {
        std::map<string, Value> variables;
        std::map<string, Function> functions;
        std::map<Type, Value> default_cast;

        Standard_Util::ANY_OBJECT_DEFINITION definition;
        Standard_Util::TYPE_DEFINITION type_info;
    };
};

namespace Noble_Standard_Lib {

};

namespace Noble {
    class Scope {

    };
    namespace Standard = Noble_Standard;
    namespace Stdlib = Noble_Standard_Lib;
};

namespace Standard = Noble_Standard;
namespace NStdlib = Noble_Standard_Lib;

#define NOBLE_STANDARD_INIT true
