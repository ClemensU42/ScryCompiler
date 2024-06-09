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

// ExprAST - Base class for all expression nodes
    class ExprAST {
    public:
        virtual ~ExprAST() = default;
    };

// I32ExprAST - Expression class for signed 32-bit integers
    class I32ExprAST : public ExprAST {
        int32_t val;

    public:
        explicit I32ExprAST(int32_t val) : val(val) {}
    };

// VariableExprAST - Expression class for referencing a variable, like "foo"
    class VariableExrpAST : public ExprAST {
        std::string name;

    public:
        explicit VariableExrpAST(std::string name) : name(std::move(name)) {}
    };

// BinaryExprAST - Expression class for binary operator
    class BinaryExprAST : public ExprAST {
        char op;
        std::unique_ptr<ExprAST> LHS, RHS;

    public:
        BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
                : op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    };

// CallExprAST - Expression class for function calls
    class CallExprAST : public ExprAST {
        std::string callee;
        std::vector<std::unique_ptr<ExprAST>> args;

    public:
        CallExprAST(const std::string &callee, std::vector<std::unique_ptr<ExprAST>> args)
                : callee(callee), args(std::move(args)) {}
    };

// PrototypeAST - This class represents the "prototype" for a function,
// which captures it's name, and it's argument names (thus implicitly the number of arguments the function takes).
    class PrototypeAST {
        std::string name;
        std::vector<std::string> args;

    public:
        PrototypeAST(const std::string &name, std::vector<std::string> args)
                : name(name), args(std::move(args)) {}
    };

// FunctionAST - This class represents a function definition itself
    class FunctionAST {
        std::unique_ptr<PrototypeAST> prototype;
        std::unique_ptr<ExprAST> body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body)
                : prototype(std::move(prototype)), body(std::move(body)) {}
    };

    int getNextToken();

    int getCurrentToken();

    void installBinopPrecedences();

    std::unique_ptr<ExprAST> LogError(const char *str);

    std::unique_ptr<PrototypeAST> LogErrorP(const char *str);

    std::unique_ptr<ExprAST> ParseI32Expr();

    std::unique_ptr<ExprAST> ParseParenExpr();

    std::unique_ptr<ExprAST> ParseIdentifierExpr();

    std::unique_ptr<ExprAST> ParsePrimary();

    std::unique_ptr<ExprAST> ParseExpression();

    std::unique_ptr<ExprAST> ParseBinOpRHS(int exprPrec, std::unique_ptr<ExprAST> LHS);

    std::unique_ptr<PrototypeAST> ParsePrototype();

    std::unique_ptr<FunctionAST> ParseDefinition();

    std::unique_ptr<PrototypeAST> ParseExtern();

    std::unique_ptr<FunctionAST> ParseTopLevelExpr();

}

#endif //SCRYCOMPILER_AST_H
