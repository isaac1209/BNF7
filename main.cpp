#include <iostream>
#include "parser.h"
#include "lexer.h"
int main() {

    std::string program = "lo* could.{3}";
    std::string input = "Waterloo I was defeated, you won the war Waterloo promise to"
                        " love you for ever more Waterloo couldn't escape if I wanted"
                        " to Waterloo knowing my fate is to be with you Waterloo finally"
                        " facing my Waterloo ";

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
