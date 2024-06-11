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

#include "lexer.h"

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

    class Expr{

    public:
        ~Expr() = default;
    };

    class VariableExpr : public Expr{
        std::string name;
        bool isMutable;
        std::string valueAsString;
    };

    class PrototypeExpr : public Expr{
        std::string name;
        std::vector<std::string> args;
    public:
        PrototypeExpr(std::string name, std::vector<std::string> args) : name(std::move(name)), args(std::move(args)){}
    };

    class Scope{
        std::map<std::string, std::unique_ptr<VariableExpr>> variables;
        std::map<std::string, Expr> functions;
    };

    class FunctionExpr : public Expr{
        std::unique_ptr<PrototypeExpr> prototype;
        std::unique_ptr<Scope> bodyScope;

    public:
        FunctionExpr(std::unique_ptr<PrototypeExpr> prototype, std::unique_ptr<Scope> bodyScope)
            : prototype(std::move(prototype)), bodyScope(std::move(bodyScope)){}
    };

    class ExternExpr : public Expr{
        std::unique_ptr<PrototypeExpr> prototype;

    public:
        ExternExpr(std::unique_ptr<PrototypeExpr> prototype)
            : prototype(std::move(prototype)) {}
    };

    std::unique_ptr<VariableExpr> ParseVariableExpression(std::vector<lexer::Token>& tokens, size_t* currentIndexPtr);

}

#endif //SCRYCOMPILER_AST_H
