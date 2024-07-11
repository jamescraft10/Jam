#include <jam.hpp>

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

    Jam::Parser parser(tokens);

    // print ast
    std::cout << "AST\n";
    std::cout << "Program {\n";
    for(int i = 0; i < parser.program.body.size(); ++i) {
        parser.program.body[i]->Print();
    }
    std::cout << "}\n\n";

    std::string output = argv[2];
    Jam::CodeGen::Generate(std::move(parser.program), output);

    std::cout << "Compiled binary at " << output << "\n";

    return EXIT_SUCCESS;
}