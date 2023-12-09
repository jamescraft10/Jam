#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

bool CheckExtension(std::string::size_type n, std::string const& s, int Length) {
    if(std::string::npos == n) {
        std::cout << "This file does not contain \".build\"\n";
        return 1;
    } else {
        if(Length - 6 == n) {
            return 0;
        } else {
            std::cout << "This file does not contain \".build\"\n";
            return 1;
        }
    }
}

int main(int argc, char* argv[]) {
    // Check for errors in the cmd arguments
    if(argc < 2) {
        std::cerr << "Must pass in a file\n";
        return EXIT_FAILURE;
    }

    // Get file contents
    std::string FilePath = argv[1];
    if(CheckExtension(FilePath.find(".build"), FilePath, FilePath.length())) {
        return EXIT_FAILURE;
    }

    std::string OneLine;
    std::ifstream Program(FilePath);
    while(std::getline(Program, OneLine)) {
        std::system((std::string(OneLine)).c_str());
    }
    Program.close();

    std::cout << "Done!\n";
    return EXIT_SUCCESS;
}
