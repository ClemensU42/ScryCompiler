//
// Created by clemens on 6/7/24.
//

#include <map>
#include "ast.h"
#include "lexer.h"
#include "consoleColors.h"


// BinopPrecedence - This holds the precedence for each binary operator that is defined
static std::map<std::string, int> BinopPrecedence;

int getBinopPrecedence(std::string& binop){
	if (!BinopPrecedence.contains(binop))
		throw std::runtime_error(std::string(COLOR_RED + binop + " is not a valid operation!"));
	return BinopPrecedence[binop];
}

void installBinopPrecedences(){
    BinopPrecedence["<<"] = 10;
	BinopPrecedence[">>"] = 10;
    BinopPrecedence["+"] = 20;
    BinopPrecedence["-"] = 20;
    BinopPrecedence["*"] = 40;
    BinopPrecedence["/"] = 40;
}

std::unique_ptr<ast::Scope> ast::ParseTopLevelScope(const std::vector<lexer::Token>& tokenArray){
    std::unique_ptr<Scope> scope;

    size_t currentTokenIndex = 0;



    return scope;
}

std::ostream& operator << (std::ostream& os, const ast::VariableExpr& varExpr){
	return os << "Variable name: " << varExpr.name
			<< "\nIs variable mutable: " << varExpr.isMutable << std::endl;
}