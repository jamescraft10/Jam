#pragma once

#include "tokenization.hpp"

std::vector<Token> Parse(std::vector<Token> Tokens) {
    // Print Token Values
    for(int i = 0; i < Tokens.size(); ++i) {
        std::cout << Tokens[i].type << "\n" << Tokens[i].value << "\n\n";
    }

    std::vector<Token> New_Tokens;
    for(int i = 0; i < Tokens.size(); ++i) {
        if(Tokens[i].type == _return) {
            New_Tokens.push_back({_return, "return"});
            if(i + 1 < Tokens.size() && Tokens[i + 1].type == int_lit) {
                for(int j = 1; Tokens[i+j].type != semi && Tokens[i+j].type != _fail; ++j) {
                    New_Tokens.push_back({int_lit, Tokens[i+j].value});
                }
            } else {
                std::cout << "Error: Expected int_lit after _return\n";
                New_Tokens.push_back({_fail, "error"});
                return New_Tokens;
            }
        } else if(Tokens[i].type == semi) {
            New_Tokens.push_back({semi, ";"});
        } else if(Tokens[i].type == _int) {
            New_Tokens.push_back({_int, ""});
        } else if(Tokens[i].type == letter || Tokens[i].type == int_lit) {
            New_Tokens.push_back(Tokens[i]);
        }
    }
    return New_Tokens;
}