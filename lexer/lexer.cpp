//
// Created by clemens on 6/6/24.
//

#include <cctype>
#include <cstdio>
#include <string>
#include "lexer.h"

static std::string IdentifierStr;   // Filled in if tok_identifier
static int32_t I32Val;                  // Filled in if tok_i32

int gettok(){
    static int lastChar = ' ';

    while(isspace(lastChar))
        lastChar = getchar();
    if(isalpha(lastChar)){ // identifier: [a-zA-Z][a-zA-Z0-9]
        IdentifierStr = std::to_string(lastChar);
        while(isalnum((lastChar = getchar())))
            IdentifierStr += std::to_string(lastChar);
        if(IdentifierStr == "fn")
            return tok_fn;
        if(IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }
    if(isdigit(lastChar)){ // Number: [0-9] // TODO: implement different types (int, float, etc.)
        std::string numStr;
        do{
            numStr += std::to_string(lastChar);
            lastChar = getchar();
        } while (isdigit(lastChar));

        I32Val = std::stoi(numStr);
        return tok_i32;
    }
    if(lastChar == '#'){
        // comment until end of line
        do
            lastChar = getchar();
        while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');
        if(lastChar != EOF)
            return gettok();
    }
    if(lastChar == EOF){ // check for end of file, don't eat it!
        return token_eof;
    }

    // otherwise, just return the character as it's ascii value
    int thisChar = lastChar;
    lastChar = getchar();
    return thisChar;
}