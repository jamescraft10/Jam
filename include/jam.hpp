#include <parser.hpp> // includes everything

namespace Jam {
    bool checkExtension(std::string::size_type n, std::string const& s, int Length);
    void usageCheck(int argc);
    std::string getFileContents(std::string path);

    namespace CodeGen {
        void Generate(Jam::Ast::Program program, std::string outputDir);
        void GenerateFile(std::string outputDir, std::string outputContent);
    };
};