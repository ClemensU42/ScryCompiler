//
// Created by clemens on 6/7/24.
//

#ifndef SCRYCOMPILER_AST_H
#define SCRYCOMPILER_AST_H

#include <cstdint>
#include <string>
#include <memory>
#include <utility>
#include <vector>

namespace ast {

    enum VariableTypes {
        i64,
        i32,
        i16,
        i8,
        u64,
        u32,
        u16,
        u8,
        f64,
        f32,
        function,
        custom_struct,
    };

    class Variable{
        std::string name;
        bool isMutable;
        std::string valueAsString;
    };


}

#endif //SCRYCOMPILER_AST_H
