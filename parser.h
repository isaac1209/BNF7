//
// Created by amthe on 2/2/2024.
//

#ifndef BNF7_PARSER_H
#define BNF7_PARSER_H
#include <iostream>
#include <vector>
#include "lexer.h"

struct op{
    virtual bool eval(it first, it last, it& ptr) = 0;
    void add(op* child){
        if(child)
            children.push_back(child);
    }
    std::vector<op*> children;
};
struct char_op:op{
    char ch;
    char_op(char c):ch(c){ }

        bool eval(it first, it last,it& ptr) override{

        if(*first == ch || *first == '.'){
            return true;
        } else{
            return false;
        }

        }

};

struct word : op{
    bool eval(it first, it last,it& ptr) override{
        auto result = children[0]->eval(first, last,ptr);

        if(first != last){
            ptr = first;
        }

        if(children.size() > 1){
            return result && children[1]->eval(++first, last,ptr);
        }
        return result;
    }
};

struct counter: op{
    int N = 0;
    counter(int c):N(c){}

    bool eval(it first, it last,it& ptr) override{
        static int n = 0; // using static in order to preserve our current value when call back
        auto result = children[0]->eval(first, last,ptr);
        if(first == last){
            return false;
        }
        if(!result){
            eval(++first, last,ptr);
        }

        last = ptr +(N +1); // uppdate the last pointer
        if(n < 1){
            n++;
            while (first != last){
                std::cout<<*first;
                first++;
            }
        }


        return result;
    }
};

struct group_op:op{ // wrong implementation
    bool eval(it first, it last,it& ptr) override{
        if(first == last)
            return false;
        auto result = children[0]->eval(first, last,ptr);
        if(result){
            return true;
        }
        return false;
    }
};

struct expr_op:op{ //
    bool eval(it first, it last,it& ptr) override{
        if(first == last)
            return false;
        auto result = children[0]->eval(first, last,ptr);
        if(result){
            return true;
        }

        return false;
    }
};


struct multi: op{   //klar
    int counter=0;
    bool eval(it first, it last,it& ptr) override{
        static int n = 0; // using static in order to preserve our current value when call back
        static std::string ord;
        auto result = children[0]->eval(first, last,ptr);
        if(first == last){
            return false;
        }
        if(!result){
            eval(++first, last,ptr);
        }

        //last = ptr +(N +1); // uppdate the last pointer
        while (first != ptr){
            ord+=*first;
            first++;
        }

            //first = ptr;
            if(n<1){
                n++;
                while (first != last){
                    if(*first == *ptr){
                        ord+=*first;
                        first++;
                    }else{
                        break;
                    }
                }
                std::cout<<ord<<'\n';
            }
        return result;
    }


};

struct or_op:op{    //klar
    bool eval(it first, it last,it& ptr) override{
        auto result = children[0]->eval(first, last,ptr);

        if(result){
            return true;
        }

        return children[1]->eval(first, last,ptr);
    }
};

struct match_op:op{
    bool eval(it first, it last,it& ptr) override{
        if(first == last)
            return false;
        auto result = children[0]->eval(first, last,ptr);
        if(!result){
            return eval(first + 1, last,ptr);
        }
        return true;
    }
};


match_op* match(it first, it last, lexer lexer);
or_op* orOp(it first, it last,lexer lexer);
word* paserWord(it& first, it last,lexer lexer);


#endif //BNF7_PARSER_H
