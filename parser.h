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

        if(*first == ch || ch == '*' || ch == '.'){
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
struct anyChar :op{
    int steps = 0;
    bool eval(it first, it last, it &ptr) override{
        static int n = steps; // using static in order to preserve our current value when call back
        auto result = children[0]->eval(first, last,ptr);
        if(first == last){
            return false;
        }
        if(!result){
            eval(++first, last,ptr);
        }

        if(steps < 0){ // då kommer inte den här structen printa ut nånting men multi kommer göra
            return result;
        }else if(steps == 0){
            while (first <= ptr+1){
                steps++;
                std::cout<<*first;
                first++;
            }
            return result;
        }
            // vi få den här att köras bara en gång

            if(n > 0){
                last = ptr + steps;
                while (first <= last){
                    std::cout<<*first;
                    first++;

                }
                n = 0; // uppdatera n så att den här while loop ska inte köra många gånger
            }







        return result;
}
};

struct multi: op{   //klar
    bool printall=0;
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
        while (first != ptr){
            ord+=*first;
            first++;
        }
            if(n<1){
                n++;
                while (first != last){
                    if(*first == *ptr  || printall){
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

expr_op* parse_expr(it& first, it last,lexer lexer);
match_op* match(it first, it last, lexer lexer);
or_op* orOp(it first, it last,lexer lexer);
word* paserWord(it& first, it last,lexer lexer);


#endif //BNF7_PARSER_H
