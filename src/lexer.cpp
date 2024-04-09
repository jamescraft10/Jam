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
            while(input.size() > 0) {
                if(input[0] == '(') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::OpenParen, "("));
                else if(input[0] == ')') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::CloseParen, ")"));
                else if(input[0] == '+' || input[0] == '-' || input[0] == '/' || input[0] == '*') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::BinaryOperator, { input[0] }));
                else if(input[0] == '=') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Equals, "="));
                else if(input[0] == ';') tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Semi, ";"));
                else {
                    // handle muticharaacter tokens
                    // handle whitespace/new lines

                    // numbers
                    if(isdigit(input[0])) {
                        std::string number;
                        while(input.size() > 0 && isdigit(input[0])) {
                            number += input[0];
                            input = input.substr(1, input.size());
                        }
                        tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Number, number));
                    } else if(isalpha(input[0])) { // identifier
                        std::string identifier;
                        while(input.size() > 0 && isalpha(input[0])) {
                            identifier += input[0];
                            input = input.substr(1, input.size());
                        }

                        // check if not keyword
                        if(keywords.find(identifier) == keywords.end()) {
                            tokens.push_back(Jam::Lexer::Token(Jam::Lexer::Identifier, identifier));
                        } else { // if keyword
                            tokens.push_back(Jam::Lexer::Token(keywords.find(identifier)->second, identifier));
                        }
                    } else if(input[0] == ' ' || input[0] == '\n' || input[0] == '\t') {
                        input = input.substr(1, input.size());
                        continue;
                    } else {
                        std::cout << "Unreconized character found in source: " << input[0] << "\n";
                        std::exit(1);
                    }
                }

                input = input.substr(1, input.size());
            }

            return tokens;
        }
    };
};