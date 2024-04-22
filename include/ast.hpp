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
                virtual ~Stmt() = default;
                virtual void Print() {
                    std::cout << "Default Stmt/Expr\n\n";
                }
        };

        class Expr : public Stmt {};

        class Program : public Stmt {
            public:
                virtual void Print() {
                    std::cout << "Program\n\n";
                }

                NodeType kind = NodeType::Program;
                std::vector<std::unique_ptr<Stmt>> body;
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
                std::string _operator;
                std::unique_ptr<Stmt> left;
                std::unique_ptr<Stmt> right;
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
                std::string symbol;
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
                std::string value;
        };
    };
};