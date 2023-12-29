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
        } else if(Tokens[i].type == num) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == _int) {
            Output += "int " + Tokens[i].value;
        } else if(Tokens[i].type == letter) {
            Output += Tokens[i].value;
        }
    }
    Output += "\n}";

    return Output;
}