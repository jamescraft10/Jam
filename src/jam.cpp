#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>

#include <jam.hpp>
#include <lexer.hpp>
#include <ast.hpp>

namespace Jam {
    bool checkExtension(std::string::size_type n, std::string const& s, int Length) {
        if(std::string::npos == n) {
            std::cout << "This file does not contain \".ja\"\n";
            return 1;
        } else {
            if(Length - 3 == n) {
                return 0;
            } else {
                std::cout << "This file does not contain \".ja\"\n";
                return 1;
            }
        }
    }

    void usageCheck(int argc) {
        // Check for errors in the cmd arguments
        if(argc < 2) {
            std::cout << "The correct usage is:\n";
            std::cout << "jam input.ja output\n";
            std::exit(EXIT_FAILURE);
        }
    }

    std::string getFileContents(std::string path) {
        std::string Contents;
        std::string oneLine;
        std::ifstream program(path);
        while(std::getline(program, oneLine)) {
            Contents += oneLine + "\n";
        }
        program.close();
        std::cout << "Contents {\n" << Contents << "}\n\n";
        return Contents;
    }
};

int main(int argc, char* argv[]) {
    Jam::usageCheck(argc);
    std::string path = argv[1];
    Jam::checkExtension(path.find(".ja"), path, path.length());
    std::string fileContents = Jam::getFileContents(path);
    std::vector<Jam::Lexer::Token> tokens = Jam::Lexer::Tokenization(fileContents);

    //Jam::Lexer::Token token1(Jam::Lexer::_return, "return");

    std::cout << "\n";
    // print tokens
    for(int i = 0; i < tokens.size(); ++i) {
        std::cout << "Token: " << tokens[i].type << "\t" << tokens[i].value << "\n";
    }

    // ast test
    Jam::Ast::NumericLiteral left;
    left.value = 15.2;

    Jam::Ast::NumericLiteral right;
    right.value = 12.6;

    Jam::Ast::BinaryExpr binaryExpr;
    binaryExpr.left = &left;
    binaryExpr.right = &right;
    binaryExpr._operator = "+";

    std::vector<Jam::Ast::Stmt*> body = {&binaryExpr};
    Jam::Ast::Program program;
    program.body = body;
    

    return EXIT_SUCCESS;
}