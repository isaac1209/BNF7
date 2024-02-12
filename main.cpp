#include <iostream>
#include "parser.h"
#include "lexer.h"
int main() {

    std::string program = "Waterloo{2}";
    std::string input = "W Waterloo ";
    lexer lexer(program.begin(),program.end());
    auto tree = match(program.begin(),program.end(),lexer);

   if(tree){
       auto match = tree->eval(input.begin(),input.end());
       if(match){
           std::cout<<"FOUND A MATCH";
       } else{
           std::cout<<"NO MATCH FOUND";
       }
   } else std::cout<<"Wrong input";



    return 0;
}
