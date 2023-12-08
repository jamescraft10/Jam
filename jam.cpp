#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum TokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::string value;
};

bool CheckIfExtension(std::string::size_type n, std::string const& s, int Length) {
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

std::vector<Token> Tokenize(const std::string str) {
    std::vector<Token> Tokens;

    for(int i = 0; i <= str.length(); ++i) {
        // Semicolen
        if(str.substr(i, 1) == ";") {
            Token token = {semi, ";"};
            Tokens.insert(Tokens.end(), 1, token);
        }

        // Return
        if(str.substr(i, 7) == "return ") {
            Token token = {_return, "return "};
            Tokens.insert(Tokens.end(), 1, token);
        }

        // Numbers
        if(std::isdigit(str[i])) {
            std::string Value;
            while(i < str.size() && (std::isdigit(str[i]) || str[i] == '.')) {
                Value += str[i];
                ++i;
            }
            --i;

            Token token = {int_lit, Value};
            Tokens.push_back(token);
        }
    }
    return Tokens;
}

int main(int argc, char* argv[]) {
    // Check for errors in the cmd arguments
    if(argc < 2) {
        std::cerr << "Must pass in a file\n";
        return EXIT_FAILURE;
    }

    std::string FilePath = argv[1];
    if(CheckIfExtension(FilePath.find(".ja"), FilePath, FilePath.length())) {
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

    // Print Token Values
    for(int i = 0; i < Tokens.size(); ++i) {
        std::cout << Tokens[i].type << "\n" << Tokens[i].value << "\n\n";
    }
    
    return EXIT_SUCCESS;
}