#ifndef _AST_
#define _AST_

#include <iostream>
#include <string>
#include <vector>

namespace Jam {
    namespace Ast {
        enum class NodeType {
            Program,
            NumericLiteral,
            Identifier,
            BinaryExpr
        };

        class Stmt {
            public:
                NodeType kind;
                virtual int kindInt() { return -1; }
                virtual ~Stmt() = default;
                virtual void Print() {
                    std::cout << "Default Stmt/Expr\n\n";
                }
                virtual std::string CodeGen() {
                    return "Default";
                }
        };

        class Expr : public Stmt {};

        class Program : public Stmt {
            public:
                virtual void Print() {
                    std::cout << "Program\n\n";
                }

                NodeType kind = NodeType::Program;
                virtual int kindInt() { return 0; }
                std::vector<std::unique_ptr<Stmt>> body;

                virtual std::string CodeGen() {
                    return "";
                }
        };

        class BinaryExpr : public Expr {
            public:
                BinaryExpr(std::string operator_ = "", std::unique_ptr<Stmt> _left = nullptr, std::unique_ptr<Stmt> _right = nullptr) {
                    _operator = operator_;
                    left = std::move(_left);
                    right = std::move(_right);
                }

                virtual void Print() {
                    std::cout << "BinaryExpr {\n";
                    std::cout << "Operator: " << _operator << "\n";
                    std::cout << "Left: ";
                    left.get()->Print();
                    std::cout << "Right ";
                    right.get()->Print();
                    std::cout << "}\n";
                }

                NodeType kind = NodeType::BinaryExpr;
                virtual int kindInt() { return 3; }
                std::string _operator;
                std::unique_ptr<Stmt> left;
                std::unique_ptr<Stmt> right;

                virtual std::string CodeGen() {
                    return "(" + left.get()->CodeGen() + _operator + right.get()->CodeGen() + ")";
                }
        };

        class Identifier : public Expr {
            public:
                Identifier(std::string _symbol) {
                    symbol = _symbol;
                }

                virtual void Print() {
                    std::cout << "Identifier {\n";
                    std::cout << "Symbol: " << symbol << "\n";
                    std::cout << "}\n";
                }

                NodeType kind = NodeType::Identifier;
                virtual int kindInt() { return 2; }
                std::string symbol;

                virtual std::string CodeGen() {
                    return symbol;
                }
        };

        class NumericLiteral : public Expr {
            public:
                NumericLiteral(std::string _value) {
                    value = _value;
                }

                virtual void Print() {
                    std::cout << "NumericLiteral {\n";
                    std::cout << "value: " << value << "\n";
                    std::cout << "}\n";
                }

                NodeType kind = NodeType::NumericLiteral;
                virtual int kindInt() { return 1; }
                std::string value;

                virtual std::string CodeGen() {
                    return value;
                }
        };
    };
};

#endif // _AST_