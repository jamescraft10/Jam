#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include <utility>
#include <error.hpp>
#include <lexer.hpp>
#include <ast.hpp>

// Orders of Prescidence
// AdditiveExpr
// MutiplicaitaveExpr
// PrimaryExpr

namespace Jam {
    namespace Parser {
        class Parser {
            public:
                Jam::Ast::Program program;
                std::vector<Jam::Lexer::Token> tokens;
                Parser(std::vector<Jam::Lexer::Token> tokens);
                std::unique_ptr<Jam::Ast::Stmt> ParseStmt();
                std::unique_ptr<Jam::Ast::Stmt> ParseExpr();
                std::unique_ptr<Jam::Ast::Stmt> ParsePrimaryExpr();
                std::unique_ptr<Jam::Ast::Stmt> ParseAdditiveExpr();
                std::unique_ptr<Jam::Ast::Stmt> ParseMultiplicitaveExpr();
        };
    };
};