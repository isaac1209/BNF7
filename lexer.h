//
// Created by amthe on 2/2/2024.
//

#ifndef BNF7_LEXER_H
#define BNF7_LEXER_H
#include <iostream>
using token = int;
using it = std::string::iterator;
class lexer {
public:
    enum {
        DIGIT=1,
        ADD_OP=2,
        MULT_OP=3,
        END=4,
        LEFT_PAREN=5,
        RIGHT_PAREN=6,
        OPEN_BRES=7,
        CLOSEING_BRES=8,
        DOT=9,
        BACK_SLASH=10,
        SPACE=11,
        LETTER,UNKOWN
    };

    lexer() = delete;
    char get_char(it& first);
    lexer(it first, it last);
    token lex(it& first, it& last);
    char lexeme();

private:
    std::string input;
    char current_lexeme;
public:
    void setCurrentLexeme(char currentLexeme);

private:
    size_t index = 0;

};


#endif //BNF7_LEXER_H
