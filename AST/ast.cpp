//
// Created by clemens on 6/7/24.
//

#include "ast.h"
#include "lexer.h"

extern int32_t I32Val;

static int currentToken;
static int getNextToken(){
    return currentToken = gettok();
}

/// LogError* - These are helper functions for error handling
std::unique_ptr<ExprAST> LogError(const char* str){
    fprintf(stderr, "Error: %s\n", str);
    return nullptr;
}

std::unique_ptr<PrototypeAST> LogErrorP(const char* str){
    LogError(str);
    return nullptr;
}

// numberexpr ::= i32
static std::unique_ptr<ExprAST> ParseI32Expr(){
    auto result = std::make_unique<I32ExprAST>(I32Val);
    getNextToken();
    return std::move(result);
}

// parenexpr ::= '(' expression ')'
static std::unique_ptr<ExprAST> ParseParenExpr(){
    getNextToken(); // eat '('
    auto v = ParseExpression();
    if (!v)
        return nullptr;

    if(currentToken != ')')
        return LogError("expected ')'");
    getNextToken(); // eat ')'
    return v;
}