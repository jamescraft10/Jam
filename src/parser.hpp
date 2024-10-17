#pragma once

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
// Statements
// AdditiveExpr
// MutiplicaitaveExpr
// PrimaryExpr

namespace Jam {
    class Parser {
        public:
            Jam::Ast::Program program;
            std::vector<Jam::Lexer::Token> tokens;

            Parser(std::vector<Jam::Lexer::Token> tokens) {
                this->tokens = tokens;

                while(this->tokens[0].type != Jam::Lexer::EOF_) {
                    this->program.body.push_back(ParseStmt());
                }
            }

            void checkIfSemi() {
                if(this->tokens[0].type != Jam::Lexer::TokenType::Semi)
                    Jam::Error::CallError("Expected semicolen after statement");
            }

            // dont have any statements to parse right now...
            std::unique_ptr<Jam::Ast::Stmt> ParseStmt() {
                switch(this->tokens[0].type) {
                    case Jam::Lexer::TokenType::Print: {
                        this->tokens.erase(this->tokens.begin()); // remove print

                        if(this->tokens[0].type != Jam::Lexer::TokenType::OpenParen)
                            Jam::Error::CallError("Expected ( in print statement");
                        this->tokens.erase(this->tokens.begin()); // remove (

                        if(this->tokens[0].type != Jam::Lexer::TokenType::String)
                            Jam::Error::CallError("Expected string in print statement");
                        std::string value = this->tokens[0].value;
                        this->tokens.erase(this->tokens.begin()); // remove value

                        if(this->tokens[0].type != Jam::Lexer::TokenType::CloseParen)
                            Jam::Error::CallError("Expected ) in print statement");
                        this->tokens.erase(this->tokens.begin()); // remove )

                        checkIfSemi();
                        this->tokens.erase(this->tokens.begin()); // remove ;
                        return std::make_unique<Jam::Ast::PrintStmt>(value);
                    }
                }

                return ParseExpr();
            }
            
            // Handle Expressions
            std::unique_ptr<Jam::Ast::Stmt> ParseExpr() {
                return ParseAdditiveExpr();
            }

            std::unique_ptr<Jam::Ast::Stmt> ParsePrimaryExpr() {
                switch(this->tokens[0].type) {
                    case Jam::Lexer::TokenType::Identifier: {
                        std::string symbol = this->tokens[0].value;
                        this->tokens.erase(this->tokens.begin());
                        return std::make_unique<Jam::Ast::Identifier>(symbol);
                    }

                    case Jam::Lexer::TokenType::Number: {
                        std::string value = this->tokens[0].value;
                        this->tokens.erase(this->tokens.begin());
                        return std::make_unique<Jam::Ast::NumericLiteral>(value);
                    }

                    case Jam::Lexer::TokenType::OpenParen: {
                        this->tokens.erase(this->tokens.begin()); // remove open paren
                        std::unique_ptr<Jam::Ast::Stmt> value = ParseExpr();
                        if(tokens[0].type != Jam::Lexer::CloseParen) {
                            Jam::Error::CallError("Unexpected token found during parenthsised expression. Expected closing parenthesis.\n");
                        }
                        this->tokens.erase(this->tokens.begin());
                        return value;
                    }

                    default:
                        Jam::Error::CallError("Unexpected token found during parsing.\n",
                                    "       Type: ", this->tokens[0].type, "\n",
                                    "       Value: ", this->tokens[0].value, "\n");
                        
                        // annoying compiler makes warning if not here
                        std::unique_ptr<Jam::Ast::Stmt> value = nullptr;
                        return value;
                };
            }

            std::unique_ptr<Jam::Ast::Stmt> ParseAdditiveExpr()  {
                Jam::Ast::BinaryExpr expression;

                expression.left = ParseMultiplicitaveExpr();

                while(this->tokens[0].value == "+" || this->tokens[0].value == "-") {
                    expression._operator = this->tokens[0].value;
                    this->tokens.erase(this->tokens.begin());

                    expression.right = ParseMultiplicitaveExpr();

                    // Create a new BinaryExpr with the current expression as left
                    expression.left = std::make_unique<Jam::Ast::BinaryExpr>(expression._operator, std::move(expression.left), std::move(expression.right));
                }

                return std::move(expression.left);
            }

            std::unique_ptr<Jam::Ast::Stmt> ParseMultiplicitaveExpr()  {
                Jam::Ast::BinaryExpr expression;

                expression.left = ParsePrimaryExpr();

                while(this->tokens[0].value == "/" || this->tokens[0].value == "*" || this->tokens[0].value == "%") {
                    expression._operator = this->tokens[0].value;
                    this->tokens.erase(this->tokens.begin());

                    expression.right = ParsePrimaryExpr();

                    // Create a new BinaryExpr with the current expression as left
                    expression.left = std::make_unique<Jam::Ast::BinaryExpr>(expression._operator, std::move(expression.left), std::move(expression.right));
                }

                return std::move(expression.left);
            }
    };
};