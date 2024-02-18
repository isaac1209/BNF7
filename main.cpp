#include <iostream>
#include "parser.h"
#include "lexer.h"
int main() {

    std::string program = "(xxx +loo)";
    std::string input = " waterloo knowinnng ";
    lexer lexer(program.begin(),program.end());
    auto tree = match(program.begin(),program.end(),lexer);
    it first = input.begin();
    it last = input.end();

   if(tree){
       auto match = tree->eval(first,last);
       if(match){
           std::cout<<" :FOUND A MATCH \n\n";
           tree->print();
       } else{
           std::cout<<"NO MATCH FOUND \n";
       }
   } else std::cout<<"Wrong input";



    return 0;
}

