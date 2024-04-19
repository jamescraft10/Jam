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
        };

        class Expr : public Stmt {};

        class BinaryExpr : public Expr {
            public:
                NodeType kind = NodeType::BinaryExpr;
                std::string _operator;
                Expr* left;
                Expr* right;
        };

        class Program : public Stmt {
            public:
                NodeType kind = NodeType::Program;
                std::vector<Stmt*> body;
        };

        class NumericLiteral : public Expr {
            public:
                NodeType kind = NodeType::NumericLiteral;
                double value; // Change later for all num types
        };
    };
};