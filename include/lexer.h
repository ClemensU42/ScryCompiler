//
// Created by clemens on 6/6/24.
//

#ifndef SKIBIDICOMPILER_LEXER_H
#define SKIBIDICOMPILER_LEXER_H

#include <vector>

namespace lexer {

    enum TokenTypes {
        tok_other,
        tok_eof,

        // commands
        tok_fn,
        tok_extern,
        tok_var,

        // primary
        tok_identifier,
        tok_number,
		tok_string,
    };

    struct Token{
        TokenTypes type;
        std::string tokenContent;
    };

	std::ostream& operator << (std::ostream& os, const Token& token);

    std::vector<Token> ParseStringToTokens(std::string source);
}

#endif //SKIBIDICOMPILER_LEXER_H
