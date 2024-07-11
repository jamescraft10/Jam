#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include <utility>

#include <parser.hpp>

namespace Jam {
    namespace CodeGen {
        void GenerateFile(std::string outputDir, std::string outputContent) {
            std::ofstream File(outputDir);
            File << outputContent;
            File.close();
        }
        
        void Generate(Jam::Ast::Program program, std::string outputDir) {
            std::string output = "#include <iostream>\nint main() {";
            for(int i = 0; i < program.body.size(); ++i) {
                std::string generated = program.body[i]->CodeGen();
                if(generated == "Default") {
                    Jam::Error::CallWarning("Unexpected AST NodeType!\n");
                } else if(program.body[i].get()->kindInt() == 1) {
                    output += "return " + generated + ";";
                } else if(program.body[i].get()->kindInt() == 3) {
                    output += "return " + generated + ";";
                } else {
                    output += generated;
                }
            }

            output += "}";
            
            if(output == "#include <iostream>\nint main() {}") {
                Jam::Error::CallWarning("No Nodes in AST!\n");
            }

            GenerateFile(outputDir+".cpp", output);
            std::string compileCpp = "g++ -o " + outputDir + " " + outputDir + ".cpp";
            std::cout << compileCpp << "\n";
            std::system(compileCpp.c_str());
        }
    };
};