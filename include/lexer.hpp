#include <vector>

namespace Jam {
    namespace Lexer {
        enum TokenType {
            Number,
            Identifier,
            Equals,
            OpenParen,
            CloseParen,
            BinaryOperator,
            Let,
            Semi,
            _EOF // end of file
        };

        class Token {
            public:
            Token(TokenType type, std::string value) {
                this->type = type;
                this->value = value;
            };
            TokenType type;
            std::string value;
        };

        std::vector<Token> Tokenization(std::string input);
        bool isOperator(char input);
    };
};