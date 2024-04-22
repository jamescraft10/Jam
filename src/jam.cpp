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

    Jam::Parser::Parser parser(tokens);

    // print ast
    std::cout << "AST\n";
    std::cout << "Program {\n";
    for(int i = 0; i < parser.program.body.size(); ++i) {
        parser.program.body[i]->Print();
    }
    std::cout << "}\n";

    return EXIT_SUCCESS;
}