#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include <utility>
#include <unordered_map>

namespace Jam {
    namespace Lexer {
        enum TokenType {
            Number,
            Identifier,
            Equals,
            OpenParen,
            CloseParen,
            BinaryOperator,
            Print,
            Semi,
            String,
            EOF_ // end of file
        };

        class Token {
            public:
            Token(TokenType type, std::string value) {
                this->type = type;
                this->value = value;
            };
            TokenType type;
            std::string value;
        };

        bool isOperator(char input) {
            return input == '+' || input == '-' || input == '/' || input == '*';
        }

        std::vector<Token> Tokenization(std::string input) {
            bool dontDelete = false;
            std::unordered_map<std::string, Jam::Lexer::TokenType> keywords = {
                {"print", Jam::Lexer::Print}
            };

            std::vector<Token> tokens;
            int line = 0;
            while(input.size() > 0) {
                if(input[0] == '(') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::OpenParen, "("));
                else if(input[0] == ')') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::CloseParen, ")"));
                else if(Jam::Lexer::isOperator(input[0])) tokens.push_back(Jam::Lexer::Token(Jam::Lexer::BinaryOperator, { input[0] }));
                else if(input[0] == '=') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Equals, "="));
                else if(input[0] == ';') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Semi, ";"));
                else if(input[0] == '"') {
                    std::string value = "";
                    input.erase(0, 1);
                    while(input[0] != '"') {
                        value += input[0];
                        input.erase(0, 1);
                    }
                    tokens.push_back(Jam::Lexer::Token(Jam::Lexer::String, value));
                }
                else if(!Jam::Lexer::isOperator(input[0])) {
                    // handle muticharaacter tokens
                    // handle whitespace/new lines

                    // numbers
                    if(isdigit(input[0])) {
                        std::string number;
                        while(input.size() > 0 && isdigit(input[0])) {
                            number += input[0];
                            input.erase(0, 1);
                        }
                        tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Number, number));
                        continue; // to this to not do the erase at the bottom of the loop
                    } else if(input[0] == ' ' || input[0] == '\n' || input[0] == '\t' || input[0] == '\r') {
                        input.erase(0, 1);
                        continue;
                    } else if(isalpha(input[0])) { // identifier
                        std::string identifier;
                        while(input.size() > 0 && isalpha(input[0])) {
                            identifier += input[0];
                            input.erase(0, 1);
                        }

                        // check if not keyword
                        if(keywords.find(identifier) == keywords.end()) {
                            tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Identifier, identifier));
                        } else { // if keyword
                            tokens.push_back(Jam::Lexer::Token(keywords.find(identifier)->second, identifier));
                        }
                        dontDelete = true; // it deletes to the last char in the string and deletes that to deleteing the next char after that so dont delete
                    } else {
                        std::cout << "Unreconized character found in source: " << input[0] << "\n";
                        std::exit(1);
                    }
                }

                if(!dontDelete) {
                    input.erase(0, 1);
                }
                dontDelete = false;
            }

            // EOF
            tokens.push_back(Jam::Lexer::Token(Jam::Lexer::EOF_, "EOF"));

            return tokens;
        }
    };
};