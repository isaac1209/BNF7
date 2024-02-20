#include <iostream>
#include "parser.h"
#include "lexer.h"
int main() {

    std::string program = "(co*) ddd";
    std::string input = " waterloooo coo ddd knowinnng couldn't";
    lexer lexer(program.begin(),program.end());
    auto tree = match(program.begin(),program.end(),lexer);
    it first = input.begin();
    it last = input.end();
       if(tree){
       auto match = tree->eval(first,last);
       if(match){
           std::cout<<" :FOUND A MATCH \n\n";
       } else{
           std::cout<<"NO MATCH FOUND \n";
       }
   } else std::cout<<"Wrong input";

    tree->print();


    return 0;
}

