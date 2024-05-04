#include <parser.hpp>

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

            while(this->tokens[0].value == "+" || this->tokens[0].value == "-") {
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