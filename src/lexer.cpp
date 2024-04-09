#include <iostream>
#include <sstream>
#include <lexer.hpp>

namespace Jam {
    namespace Lexer {
        std::vector<Token> Tokenization(std::string input) {
            // return 102;
            // {_return, "return"}, {_num, "102"}, {_semi, ";"}
            // * ignore all spaces and \n
            
            // have a "pointer" that goes through the entire file if its " " || "\n" then ignore it if its a number or a char then dont ignore it
            // if p through p+6 == "return" ......

            // TODO make this fast with hash map to store keywords or something just to make it fast

            std::vector<Token> tokens;

            for(int i = 0; i < input.size(); ++i) {
                if(input.substr(i, 6) == "return") {
                    std::cout <<  "Return\t" << input.substr(i, 6) << "\n";
                    Jam::Lexer::Token token(Jam::Lexer::_return, "return");
                    tokens.push_back(token);
                } else if(input[i] == ';') {
                    std::cout <<  "Semi\t" << input[i] << "\n";
                    Jam::Lexer::Token token(Jam::Lexer::_semi, ";");
                    tokens.push_back(token);
                } else if(isdigit(input[i])) {
                    std::cout <<  "Number\t" << input[i] << "\t" << std::to_string(input[i]-48) << "\n";
                    Jam::Lexer::Token token(Jam::Lexer::_num, std::to_string(input[i]-48)); // -48 because acsii is really stupid
                    tokens.push_back(token);
                } else {
                    continue;
                }
            }

            return tokens;
        }
    };
};