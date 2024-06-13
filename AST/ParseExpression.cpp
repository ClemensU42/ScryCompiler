//
// Created by clemens on 12.06.24.
//

#include "ast.h"
#include "lexer.h"

std::unique_ptr<ast::Expr> ast::ParseExpression(const std::vector<lexer::Token> &tokens, size_t *currentIndexPtr) {
	if(tokens[*currentIndexPtr].tokenContent == "var"){
		(*currentIndexPtr)++;
		return ast::ParseVariableExpression(tokens, currentIndexPtr);
	}
	return nullptr;
}