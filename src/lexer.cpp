#include <iostream>
#include <unordered_map>
#include <lexer.hpp>

namespace Jam {
    namespace Lexer {
        std::vector<Token> Tokenization(std::string input) {
            // TODO make this fast with hash map to store keywords or something just to make it fast

            std::unordered_map<std::string, Jam::Lexer::TokenType> keywords = {
                {"let", Jam::Lexer::Let}
            };

            std::vector<Token> tokens;
            int line = 0;
            while(input.size() > 0) {
                if(input[0] == '(') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::OpenParen, "("));
                else if(input[0] == ')') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::CloseParen, ")"));
                else if(isOperator(input[0])) tokens.push_back(Jam::Lexer::Token(Jam::Lexer::BinaryOperator, { input[0] }));
                else if(input[0] == '=') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Equals, "="));
                else if(input[0] == ';') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Semi, ";"));
                else if(!isOperator(input[0])) {
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
                    } else {
                        std::cout << "Unreconized character found in source: " << input[0] << "\n";
                        std::exit(1);
                    }
                }

                input.erase(0, 1);
            }

            // EOF
            tokens.push_back(Jam::Lexer::Token(Jam::Lexer::_EOF, "EOF"));

            return tokens;
        }

        bool isOperator(char input) {
            return input == '+' || input == '-' || input == '/' || input == '*';
        }
    };
};