#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include <utility>

#include <codegen.hpp>

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