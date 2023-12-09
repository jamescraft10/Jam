#pragma once

#include <string>
#include <vector>
#include "tokenization.hpp"

std::string JamToC(std::vector<Token> Tokens) {
    std::string Output = "int main(void) {\n";

    for(int i = 0; i < Tokens.size(); ++i) {
        if(Tokens[i].type == _return) {
            Output += "return ";
        } else if(Tokens[i].type == semi) {
            Output += ";\n";
        } else if(Tokens[i].type == int_lit) {
            Output += Tokens[i].value;
        }
    }
    Output += "\n}";

    return Output;
}