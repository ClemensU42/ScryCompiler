//
// Created by clemens on 6/6/24.
//

#ifndef SKIBIDICOMPILER_LEXER_H
#define SKIBIDICOMPILER_LEXER_H

enum Token{
    token_eof = -1,

    // commands
    tok_fn = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_i32 = -5
};

int gettok();

#endif //SKIBIDICOMPILER_LEXER_H
