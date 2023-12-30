#pragma once

#include <iostream>
#include "tokenization.hpp"

std::vector<Token> Parse(std::vector<Token> Tokens) {
    std::vector<Token> New_Tokens;
    for(int i = 0; i < Tokens.size(); ++i) {
        if(Tokens[i].type == _return) {
            New_Tokens.push_back({_return, "return"});
            if((i+1 < Tokens.size() && Tokens[i+1].type == num) || Tokens[i+1].type == letter) {
                continue; // continue to not activate else and error handle while still adding the num later in code
            } else {
                std::cout << "Error: Expected num after _return\n";
                New_Tokens.push_back({_fail, "error"});
                return New_Tokens;
            }
        } else if(Tokens[i].type == semi) { // Add logic
            New_Tokens.push_back({semi, ";"});
        } else if(Tokens[i].type == _int) {
            New_Tokens.push_back({_int, ""});
        } else if(Tokens[i].type == _double) {
            New_Tokens.push_back({_double, ""});
        } else if(Tokens[i].type == _float) {
            New_Tokens.push_back({_float, ""});
        } else if(Tokens[i].type == _bool) {
            New_Tokens.push_back({_bool, ""});
        } else if(Tokens[i].type == letter || Tokens[i].type == num) {
            New_Tokens.push_back(Tokens[i]);
        } else if(Tokens[i].type == openPara) {
            New_Tokens.push_back(Tokens[i]);
        } else if(Tokens[i].type == closePara) {
            New_Tokens.push_back(Tokens[i]);
        } else if(Tokens[i].type == print) {
            New_Tokens.push_back(Tokens[i]);
        } else if(Tokens[i].type == openParaz) {
            New_Tokens.push_back(Tokens[i]);
        } else if(Tokens[i].type == closeParaz) {
            New_Tokens.push_back(Tokens[i]);
        } else if(Tokens[i].type == openParazz) {
            New_Tokens.push_back(Tokens[i]);
        } else if(Tokens[i].type == closeParazz) {
            New_Tokens.push_back(Tokens[i]);
        }
    }
    return New_Tokens;
}