//
// Created by clemens on 6/6/24.
//

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>

#include "lexer.h"
#include "consoleColors.h"

static const std::set<std::string> doubleCharOperators = {
		"++",
		"--",
		"+=",
		"-=",
		"^=",
		"*=",
		"/=",
		"==",
		"!=",
		"<=",
		">=",
		"&=",
		"&&",
		"||",
		"|=",
		"::",
		"//",
		"..",
		"<-",
		"->"
};

/**
 * Separates all tokens in the input string and stores them in a vector
 * @param source - is the input string that should be tokenized
 * @return std::vector<lexer::Token> - is the output vector that contains all tokens
 */
std::vector<lexer::Token> lexer::ParseStringToTokens(std::string source) {
	std::vector<lexer::Token> tokens = std::vector<lexer::Token>();

	std::cout << "source length: " << source.length() << std::endl;

	// separate each token
	size_t i = 0;
	while (i < source.length()) {
		std::string currentToken;
		// skip any whitespace
		while (isspace(source[i])) i++;

		// numbers
		if(isdigit(source[i])){
			currentToken += source[i++];
			while(isdigit(source[i]) || source[i] == '.')
				currentToken += source[i++];
			// check if number is valid
			uint16_t pointAmountInNum = 0;
			for(size_t k = 0; k < currentToken.length(); k++)
				pointAmountInNum += (uint8_t)(currentToken[k] == '.');

			TokenTypes currentNumType;

			if(pointAmountInNum == 0)
				currentNumType = TokenTypes::tok_int;
			else if (pointAmountInNum == 1)
				currentNumType = TokenTypes::tok_float;
			else
				throw std::runtime_error(COLOR_RED + currentToken + " is not a valid number!");

			tokens.push_back(lexer::Token{currentNumType, currentToken});
			continue;
		}

		// names, identifiers, etc.
		if (isalnum(source[i])) {
			currentToken += source[i++];
			while (isalnum(source[i]))
				currentToken += source[i++];

			TokenTypes currentTokenType;

			if (currentToken == "fn")
				currentTokenType = TokenTypes::tok_fn;
			else if (currentToken == "extern")
				currentTokenType = TokenTypes::tok_extern;
			else if (currentToken == "var")
				currentTokenType = TokenTypes::tok_var;
			else
				currentTokenType = TokenTypes::tok_identifier;

			tokens.push_back(lexer::Token{currentTokenType, currentToken});
			continue;
		}

		if (source[i] == EOF) {
			tokens.push_back(lexer::Token{TokenTypes::tok_eof, ""});
			continue;
		}

		// tokenize other characters like ')', '+', etc.
		if (isascii(source[i])) {
			char firstChar = source[i++]; // store the current char in its own variable to avoid excess memory access
			currentToken += firstChar;

			// check if it's a string
			if (firstChar == '\"') {
				while (true) {
					if (i == source.length() - 1)
						throw std::runtime_error(COLOR_RED + "String has not been terminated!");

					currentToken += source[i];
					if (source[i++] == '\"') break;
				}
				tokens.push_back(lexer::Token{TokenTypes::tok_string, currentToken});
				continue;
			}

			// check for certain longer operators like ++, --, ==, etc. to turn them into a single token
			if (i < source.length()) { // check if 'i' is not the last character, so we don't access invalid memory
				char nextChar = source[i];

				std::string doubleCharToken(1, firstChar);
				doubleCharToken += nextChar;
				if (doubleCharOperators.find(doubleCharToken) != doubleCharOperators.end()) {
					// 'doubleCharToken' is contained in the 'doubleCharOperators' vector
					currentToken = doubleCharToken;
					i++;
				}
			}

			if(currentToken == "//"){ // skip until the end of the line as this is a comment
				while(source[i] != '\n') i++;
				continue;
			}

			tokens.push_back(lexer::Token{TokenTypes::tok_other, currentToken});
			continue;
		}
	}
	return tokens;
}

static std::vector<std::string> tokenTypeNames = {
		"Token_Other",
		"Token_EOF",

		// commands
		"Token_Fn",
		"Token_Extern",
		"Token_Var",

		// primary
		"Token_Identifier",
		"Token_Integer",
		"Token_Float",
		"Token_String",
};

std::ostream &lexer::operator<<(std::ostream &os, const lexer::Token &token) {
	return os << "Token Content: " << token.tokenContent
			  << "\t\tToken Type: " << tokenTypeNames[token.type];
}
