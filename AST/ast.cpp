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

void ast::installBinopPrecedences(){
    BinopPrecedence["<<"] = 10;
	BinopPrecedence[">>"] = 10;
    BinopPrecedence["+"] = 20;
    BinopPrecedence["-"] = 20;
    BinopPrecedence["*"] = 40;
}
