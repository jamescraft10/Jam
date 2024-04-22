#include <parser.hpp>

/*
namespace Jam {
    namespace Parser {
        Jam::Ast::Program ProduceAST(std::vector<Jam::Lexer::Token> tokens) {
            Jam::Ast::Program program;

            while(tokens[0].type != Jam::Lexer::EOF_) {
                std::cout << "hi\n";
                // print tokens
                for(int i = 0; i < tokens.size(); ++i) {
                    std::cout << "Token: " << tokens[i].type << "\t" << tokens[i].value << "\n";
                }
                std::cout << "\n\n";
                program.body.push_back(ParseStmt(tokens));
                tokens.erase(tokens.begin());
            }

            return program;
        }

        // dont have any statements to parse right now...
        std::unique_ptr<Jam::Ast::Stmt> ParseStmt(std::vector<Jam::Lexer::Token> tokens) {
            return ParseExpr(tokens);
        }

        // Handle Expressions
        std::unique_ptr<Jam::Ast::Stmt> ParseExpr(std::vector<Jam::Lexer::Token> tokens) {
            return ParseAdditiveExpr(tokens);
        }

        std::unique_ptr<Jam::Ast::Stmt> ParsePrimaryExpr(std::vector<Jam::Lexer::Token> tokens) {
            switch(tokens[0].type) {
                case Jam::Lexer::TokenType::Identifier: {
                    return std::make_unique<Jam::Ast::Identifier>(tokens[0].value);
                }

                case Jam::Lexer::TokenType::Number: {
                    return std::make_unique<Jam::Ast::NumericLiteral>(tokens[0].value);
                }

                case Jam::Lexer::TokenType::OpenParen: {
                    return std::make_unique<Jam::Ast::NumericLiteral>(tokens[0].value);
                }

                case Jam::Lexer::TokenType::CloseParen: {
                    return std::make_unique<Jam::Ast::NumericLiteral>(tokens[0].value);
                }

                default:
                    std::cerr << "Unexpected token found during parsing.\n";
                    std::cerr << "Type: " << tokens[0].type << "\n";
                    std::cerr << "Value: " << tokens[0].value << "\n";
                    exit(-1);
            };
        }

        std::unique_ptr<Jam::Ast::Stmt> ParseAdditiveExpr(std::vector<Jam::Lexer::Token> tokens) {
            std::cout << "hii\n";
            // print tokens
            for(int i = 0; i < tokens.size(); ++i) {
                std::cout << "Token: " << tokens[i].type << "\t" << tokens[i].value << "\n";
            }
            std::cout << "\n\n";

            Jam::Ast::BinaryExpr expression;

            std::unique_ptr<Jam::Ast::Stmt> left = ParsePrimaryExpr(tokens);
            tokens.erase(tokens.begin());
            expression.left = std::move(left);

            std::unique_ptr<Jam::Ast::Stmt> right;
            std::string _operator;

            while(tokens[0].value == "+" || tokens[0].value == "-") {
                std::cout << "hiii\n";
                // print tokens
                for(int i = 0; i < tokens.size(); ++i) {
                    std::cout << "Token: " << tokens[i].type << "\t" << tokens[i].value << "\n";
                }
                std::cout << "\n\n";

                std::string _operator = tokens[0].value;
                tokens.erase(tokens.begin());
                
                right = ParsePrimaryExpr(tokens);

                expression.right = std::move(right);
                expression._operator = _operator;
            }
            
            return std::make_unique<Jam::Ast::BinaryExpr>(expression._operator, std::move(expression.left), std::move(expression.right));
        }
    };
};
*/

namespace Jam {
    namespace Parser {
        Parser::Parser(std::vector<Jam::Lexer::Token> tokens) {
            this->tokens = tokens;

            while(this->tokens[0].type != Jam::Lexer::EOF_) {
                this->program.body.push_back(ParseStmt());
            }
        }

        // dont have any statements to parse right now...
        std::unique_ptr<Jam::Ast::Stmt> Parser::ParseStmt() {
            return ParseExpr();
        }

        // Handle Expressions
        std::unique_ptr<Jam::Ast::Stmt> Parser::ParseExpr() {
            return ParseAdditiveExpr();
        }

        std::unique_ptr<Jam::Ast::Stmt> Parser::ParsePrimaryExpr() {
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
            };
        }

        std::unique_ptr<Jam::Ast::Stmt> Parser::ParseAdditiveExpr() {
           Jam::Ast::BinaryExpr expression;

            expression.left = ParseMultiplicitaveExpr();

            while (this->tokens[0].value == "+" || this->tokens[0].value == "-") {
                expression._operator = this->tokens[0].value;
                this->tokens.erase(this->tokens.begin());

                expression.right = ParseMultiplicitaveExpr();

                // Create a new BinaryExpr with the current expression as left
                expression.left = std::make_unique<Jam::Ast::BinaryExpr>(expression._operator, std::move(expression.left), std::move(expression.right));
            }

            return std::move(expression.left);
        }

        std::unique_ptr<Jam::Ast::Stmt> Parser::ParseMultiplicitaveExpr() {
            Jam::Ast::BinaryExpr expression;

            expression.left = ParsePrimaryExpr();

            while (this->tokens[0].value == "/" || this->tokens[0].value == "*" || this->tokens[0].value == "%") {
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