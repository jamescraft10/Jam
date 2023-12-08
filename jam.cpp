#include <iostream>
#include <fstream>
#include <string>

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

int main(int argc, char* argv[]) {
    // Check for errors in the cmd arguments
    if(argc < 2) {
        std::cout << "Must pass in a file\n";
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
    
    // Lexical Analysis
    for(int i = 0; i <= FileContents.length(); ++i) {
        // Semicolen
        if(FileContents.substr(i, 1) == ";") {
            std::cout << ";\n";
        }

        // Return
        if(FileContents.substr(i, 7) == "return ") {
            std::cout << "return \n";
        }
    }

    return EXIT_SUCCESS;
}