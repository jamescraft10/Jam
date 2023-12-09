#include <vector>
#include <string>
#pragma once

enum TokenType {
    _return,
    int_lit,
    semi,
    _fail
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> Tokenize(const std::string str) {
    std::vector<Token> Tokens;

    for(int i = 0; i <= str.length(); ++i) {
        if(str.substr(i, 1) == ";") {                    // Semicolen
            Token token = {semi, ";"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 7) == "return ") {       // Return
            i+=6;
            Token token = {_return, "return "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(std::isdigit(str[i]) || str[i] == '=' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {                // Numbers
            Token token = {int_lit, str.substr(i, 1)};
            Tokens.push_back(token);
        } else if(std::isspace(str[i])) {
            continue;
        } else if(std::isalpha(str[i])) {
            continue;
        }
    }
    return Tokens;
}