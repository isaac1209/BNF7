//
// Created by amthe on 2/2/2024.
//

#ifndef BNF7_PARSER_H
#define BNF7_PARSER_H
#include <iostream>
#include <vector>
#include "lexer.h"

struct op{ //klar
    virtual bool eval(it& first, it last) = 0;
    void add(op* child){
        if(child)
            children.push_back(child);
    }
    std::vector<op*> children;
};
struct word : op{ // klar
    bool eval(it& first, it last) override{
        auto result = children[0]->eval(first, last);
        if(children.size() > 1){
            ++first;
            return result && children[1]->eval(first, last);
        }
        return result;
    }
};
struct char_op:op{ //klar
    char ch;
    char_op(char c):ch(c){ }
        bool eval(it& first, it last) override{

        if(*first == ch || ch == '.'){
            return true;
        } else{
            return false;
        }

        }

};
struct anyChar :char_op{ //klar
    anyChar(): char_op('\0'){}
    bool eval(it& first, it last) override{
        std::cout<<*first;
        return true;
    }
};
struct multi: op{   //klar
    std::string myString="";
    bool eval(it& first, it last) override{

        while ( children[0]->eval(first,last)){
            myString+=*first;
            if(first == last){ return true;}
            first++;
        }

        if(!myString.empty()){
            std::cout<<myString<<std::endl;
            return true;
        }
        return false;
    }

};
struct expr_op:op{ //   klar
    bool eval(it& first, it last) override{
        if(first == last)
            return false;
        auto result = children[0]->eval(first, last);
        if(result){
            return true;
        }
        return false;
    }
};
struct subexpr:op{ //klar

    bool eval(it& first, it last) override{
        bool result=children[0]->eval(first,last);
        if (result) return true;
        return false;
    }

};
struct group_op:op{ // klar
    bool eval(it& first, it last) override{
        if(first == last)
            return false;
        auto result = children[0]->eval(first, last);
        if(result){
            return true;
        }
        return false;
    }
};

struct counter: op{
    int N = 0;
    counter(int c):N(c){}
    bool eval(it& first, it last) override{
        last = first + N;
        while (children[0]->eval(first,last)){
            if(first == last){
                break;
            }
            std::cout<<*first;
            first++;
        }

        return first == last;
    }
};




struct or_op:op{
    bool eval(it& first, it last) override{
        auto result = children[0]->eval(first, last);
        if(result){
            return true;
        }
        return children[1]->eval(first, last);
    }
};


struct match_op:op{
    bool eval(it& first, it last) override{
        if(first == last)
            return false;
        auto result = children[0]->eval(first, last);
        if(!result){
            return eval(first, last);
        }
        return true;
    }
};



multi* multiParser(it& first, it last,lexer lexer);
expr_op* parse_expr(it& first, it last,lexer lexer);
match_op* match(it first, it last, lexer lexer);
or_op* orOp(it first, it last,lexer lexer);
word* paserWord(it& first, it last,lexer lexer);
char_op* charOp(it first, it last,lexer lexer);
counter* count(it& first, it last,lexer lexer);

#endif //BNF7_PARSER_H
