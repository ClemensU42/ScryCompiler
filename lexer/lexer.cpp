//
// Created by clemens on 6/6/24.
//

#include <cctype>
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
		"//"
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

		// tokenize names, identifiers, numbers, etc.
		if (isalnum(source[i])) {
			currentToken += source[i++];
			while (isalnum(source[i]))
				currentToken += source[i++];

			TokenTypes currentTokenType = TokenTypes::tok_identifier;

			if (currentToken == "fn")
				currentTokenType = TokenTypes::tok_fn;
			else if (currentToken == "extern")
				currentTokenType = TokenTypes::tok_extern;
			else if (currentToken == "var")
				currentTokenType = TokenTypes::tok_var;

			for (size_t j = 0; j < currentToken.length(); j++) {
				if (!(isdigit(currentToken[j]) || currentToken[j] == '.')) break;
				if (j == (currentToken.length()-1))
					currentTokenType = TokenTypes::tok_number;
			}

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
					if (i == source.length() - 1) {
						std::cerr << RED << "String has not been terminated!" << RESET << std::endl;
						return {};
					}

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
		"Token_Number",
		"Token_String",
};

std::ostream &lexer::operator<<(std::ostream &os, const lexer::Token &token) {
	return os << "Token Content: " << token.tokenContent
			  << "\t\t\tToken Type: " << tokenTypeNames[token.type];
}
