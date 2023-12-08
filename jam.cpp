#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum TokenType {
    _return,
    int_lit,
    semi,
    _fail
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
        if(str.substr(i, 1) == ";") {                    // Semicolen
            Token token = {semi, ";"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 7) == "return ") {       // Return
            i+=6;
            Token token = {_return, "return "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(std::isdigit(str[i])) {                // Numbers
            Token token = {int_lit, str.substr(i, 1)};
            Tokens.push_back(token);
        } else if(std::isspace(str[i])) {
            continue;
        } else if(std::isalpha(str[i])) {
            continue;
        }
    }
    return Tokens;
}

std::string JamToC(std::vector<Token> Tokens) {
    std::string Output = "int main(void) {\n";

    for(int i = 0; i < Tokens.size(); ++i) {
        if(Tokens[i].type == _return) {
            Output += "return ";
        } else if(Tokens[i].type == semi) {
            Output += ";\n";
        } else if(Tokens[i].type == int_lit) {
            Output += Tokens[i].value;
        }
    }
    Output += "\n}";

    return Output;
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////// To get something that i can see i am going to convert the tokens into c without doing the rest ///////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Jam to C
    std::string Output = JamToC(Tokens);

    // Create File
    std::ofstream File("output.c");
    File << Output;
    File.close();

    return EXIT_SUCCESS;
}