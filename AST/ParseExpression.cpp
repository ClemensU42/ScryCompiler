//
// Created by clemens on 12.06.24.
//

#include <iostream>
#include "ast.h"
#include "lexer.h"

std::unique_ptr<ast::Expr> ast::ParseExpression(const std::vector<lexer::Token> &tokens, size_t *currentIndexPtr) {
	if(tokens[*currentIndexPtr].tokenContent == "var"){
		(*currentIndexPtr)++;
		std::unique_ptr<ast::VariableExpr> varExpr = ast::ParseVariableExpression(tokens, currentIndexPtr);
        std::cout << *varExpr << std::endl;
	}
	return nullptr;
}