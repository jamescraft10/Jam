#include <jam.hpp>

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

    // print tokens
    for(int i = 0; i < tokens.size(); ++i) {
        std::cout << "Token: " << tokens[i].type << "\t" << tokens[i].value << "\n";
    }
    std::cout << "\n";

    // Jam::Ast::Program program = Jam::Parser::ProduceAST(tokens);
    Jam::Parser::Parser parser(tokens);

    std::cout << "Program {\n";
    for(int i = 0; i < parser.program.body.size(); ++i) {
        parser.program.body[i]->Print();
    }
    std::cout << "}\n";

    // TODO: make a function to print a ast so i dont do this everytime i wanna
    // also make it so i can easyily get the values of every element
    
    // Jam::Ast::BinaryExpr* binaryExpr = dynamic_cast<Jam::Ast::BinaryExpr*>(parser.program.body[0].get());
    // std::cout << "Operator: " << binaryExpr->_operator << "\n";
    // std::cout << "Left Value: " << ((Jam::Ast::NumericLiteral*)binaryExpr->left.get())->value << "\n";

    return EXIT_SUCCESS;
}