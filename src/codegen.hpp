#pragma once

#include <string>
#include <vector>
#include "tokenization.hpp"

std::string JamToC(std::vector<Token> Tokens) {
    std::string Output = "#include <stdio.h>\n#include <stdbool.h>\n";

    for(int i = 0; i < Tokens.size(); ++i) {
        if(Tokens[i].type == _return) {
            Output += "return ";
        } else if(Tokens[i].type == semi) {
            Output += ";\n";
        } else if(Tokens[i].type == num) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == _int) {
            Output += "int " + Tokens[i].value;
        } else if(Tokens[i].type == _float) {
            Output += "float " + Tokens[i].value;
        } else if(Tokens[i].type == _double) {
            Output += "double " + Tokens[i].value;
        } else if(Tokens[i].type == _bool) {
            Output += "bool " + Tokens[i].value;
        } else if(Tokens[i].type == letter) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == openPara) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == closePara) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == print) {
            Output += "printf";
        } else if(Tokens[i].type == openParaz) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == closeParaz) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == openParazz) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == closeParazz) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == _void) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == _char) {
            Output += Tokens[i].value;
        } else if(Tokens[i].type == _input) {
            Output += Tokens[i].value;
        }
    }

    return Output;
}