//
// Created by clemens on 11.06.24.
//

#include <map>
#include "ast.h"

std::map<std::string, ast::VariableTypes> StringsOfVariableTypes = {
        std::pair("i64", ast::VariableTypes::i64),
        std::pair("i32", ast::VariableTypes::i32),
        std::pair("i16", ast::VariableTypes::i16),
        std::pair("i8", ast::VariableTypes::i8),

        std::pair("u64", ast::VariableTypes::u64),
        std::pair("u32", ast::VariableTypes::u32),
        std::pair("u16", ast::VariableTypes::u16),
        std::pair("u8", ast::VariableTypes::u8),

        std::pair("f64", ast::VariableTypes::f64),
        std::pair("f32", ast::VariableTypes::f32),

        std::pair("function", ast::VariableTypes::function),
};

std::unique_ptr<ast::VariableExpr> ast::ParseVariableExpression(std::vector<lexer::Token>& tokens, size_t* currentIndexPtr){

}