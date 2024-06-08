//
// Created by clemens on 6/7/24.
//

#include <map>
#include "ast.h"
#include "lexer.h"


// BinopPrecedence - This holds the precedence for each binary operator that is defined
static std::map<char, int> BinopPrecedence;
/// GetTokPrecedence - Get the precedence of the pending binary operator token
/*static int getTokPrecedence() {
    if(!isascii(currentToken))
        return -1;

    // Make sure it's a declared binop
    int tokPrec = BinopPrecedence[currentToken];
    if(tokPrec <= 0) return -1;
    return tokPrec;
}*/

void ast::installBinopPrecedences(){
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40;
}
/*
/// LogError* - These are helper functions for error handling
std::unique_ptr<ast::ExprAST> ast::LogError(const char* str){
    fprintf(stderr, "Error: %s\n", str);
    return nullptr;
}

std::unique_ptr<ast::PrototypeAST> ast::LogErrorP(const char* str){
    LogError(str);
    return nullptr;
}

// numberexpr ::= i32
std::unique_ptr<ast::ExprAST> ast::ParseI32Expr(){
    auto result = std::make_unique<ast::I32ExprAST>(lexer::getI32Val());
    ast::getNextToken();
    return std::move(result);
}

// parenexpr ::= '(' expression ')'
std::unique_ptr<ast::ExprAST> ast::ParseParenExpr(){
    ast::getNextToken(); // eat '('
    auto v = ast::ParseExpression();
    if (!v)
        return nullptr;

    if(currentToken != ')')
        return ast::LogError("expected ')'");
    ast::getNextToken(); // eat ')'
    return v;
}

// identifiertexpr
//      ::= identifier
//      ::= identifier '(' expression* ')'
std::unique_ptr<ast::ExprAST> ast::ParseIdentifierExpr(){
    std::string idName = lexer::getIdentifierStr();
    ast::getNextToken();

    if(currentToken != '(') // simple variable ref
        return std::make_unique<ast::VariableExrpAST>(idName);

    // Call
    ast::getNextToken();
    std::vector<std::unique_ptr<ast::ExprAST>> args;
    if(currentToken != ')'){
        while(true){
            if(auto arg = ast::ParseExpression())
                args.push_back(std::move(arg));
            else
                return nullptr;

            if(currentToken == ')')
                break;

            if(currentToken != ',')
                return LogError("Expected ')' or ',' in argument list");
            ast::getNextToken();
        }
    }

    // eat the ')'
    ast::getNextToken();

    return std::make_unique<ast::CallExprAST>(idName, std::move(args));
}

std::unique_ptr<ast::ExprAST> ast::ParsePrimary(){
    switch (currentToken) {
        default:
            return ast::LogError("unknown token when expecting an expression");
        case lexer::tok_identifier:
            return ast::ParseIdentifierExpr();
        case lexer::tok_i32:
            return ast::ParseI32Expr();
        case '(':
            return ParseParenExpr();
    }
}

std::unique_ptr<ast::ExprAST> ast::ParseExpression(){
    auto LHS = ast::ParsePrimary();
    if(!LHS)
        return nullptr;
    return ParseBinOpRHS(0, std::move(LHS));
}

std::unique_ptr<ast::ExprAST> ast::ParseBinOpRHS(int exprPrec, std::unique_ptr<ast::ExprAST> LHS){
    // if this is a binop, find its precedence
    while(true){
        int tokPrec = getTokPrecedence();

        // If this is a binop that binds at least as tightly as the current binop, consume it,
        // otherwise we are done
        if (tokPrec < exprPrec)
            return LHS;

        // this is a binop
        int binOp = currentToken;
        ast::getNextToken(); // eat binop

        // Parse primary expr after the binary operator
        auto RHS = ast::ParsePrimary();
        if(!RHS)
            return nullptr;

        // If binOp binds less tightly with RHS than the operator after RHS, let
        // the pending operator take RHS as it's LHS
        int nextPrec = getTokPrecedence();
        if(tokPrec < nextPrec){
            RHS = ast::ParseBinOpRHS(tokPrec+1, std::move(RHS));
            if(!RHS)
                return nullptr;
        }
        // Merge LHS/RHS
        LHS = std::make_unique<ast::BinaryExprAST>(binOp, std::move(LHS), std::move(RHS));
    }
}

/// prototype
///     ::= id '(' id* ')'
std::unique_ptr<ast::PrototypeAST> ast::ParsePrototype(){
    if(currentToken != lexer::tok_identifier)
        return ast::LogErrorP("Expected function name in prototype");

    std::string fnName = lexer::getIdentifierStr();
    ast::getNextToken();

    if(currentToken != '(')
        return ast::LogErrorP("Expected '(' in prototype");

    // Read the list of argument names
    std::vector<std::string> argNames;
    while(ast::getNextToken() == lexer::tok_identifier)
        argNames.push_back(lexer::getIdentifierStr());
    if(currentToken != ')')
        return ast::LogErrorP("Expected ')' in prototype");

    // success
    ast::getNextToken(); // eat ')'

    return std::make_unique<ast::PrototypeAST>(fnName, std::move(argNames));
}

/// definition ::= 'fn' prototype expression
std::unique_ptr<ast::FunctionAST> ast::ParseDefinition(){
    ast::getNextToken(); // eat fn
    auto proto = ast::ParsePrototype();
    if(!proto) return nullptr;

    if(auto e = ast::ParseExpression())
        return std::make_unique<ast::FunctionAST>(std::move(proto), std::move(e));
    return nullptr;
}

/// external ::= 'extern' prototype
std::unique_ptr<ast::PrototypeAST> ast::ParseExtern(){
    ast::getNextToken(); // eat extern
    return ast::ParsePrototype();
}

/// toplevelexpr ::= expression
std::unique_ptr<ast::FunctionAST> ast::ParseTopLevelExpr(){
    if(auto e = ast::ParseExpression()){
        // Make anonymous proto
        auto proto = std::make_unique<ast::PrototypeAST>("__anon_expr", std::vector<std::string>());
        return std::make_unique<ast::FunctionAST>(std::move(proto), std::move(e));
    }
    return nullptr;
}
*/