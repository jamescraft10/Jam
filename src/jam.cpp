#include <iostream>
#include <fstream>
#include <cstdlib>

#include "tokenization.hpp"
#include "parser.hpp"
#include "codegen.hpp"

bool CheckExtension(std::string::size_type n, std::string const& s, int Length) {
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

int main(int argc, char* argv[]) {
    // Check for errors in the cmd arguments
    if(argc < 2) {
        std::cerr << "Must pass in a file and a output\n";
        return EXIT_FAILURE;
    }

    std::string FilePath = argv[1];
    if(CheckExtension(FilePath.find(".ja"), FilePath, FilePath.length())) {
        return EXIT_FAILURE;
    }

    // Get file contents
    std::string FileContents;
    std::string OneLine;
    std::ifstream Program(FilePath);
    while(std::getline(Program, OneLine)) {
        FileContents += OneLine;
    }
    Program.close();
    
    // Get Tokens
    std::vector<Token> Tokens = Tokenize(FileContents);

    // Parse Tokens
    Tokens = Parse(Tokens);
    Token ErrorToken = {_fail,"fail"};
    if(Tokens[0].type == ErrorToken.type) {
        std::cout << "Error\n";
        return EXIT_FAILURE;
    }

    // Jam to C
    std::string Output = JamToC(Tokens);

    // Create File
    std::string OutputFileC = argv[2];   OutputFileC += ".c";
    std::ofstream File(OutputFileC);
    File << Output;
    File.close();

    // Compile The C
    std::system(("g++ -o " + std::string(argv[2]) + " " + OutputFileC).c_str());

    return EXIT_SUCCESS;
}