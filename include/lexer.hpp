#include <vector>

namespace Jam {
    namespace Lexer {
        enum TokenType {
            _return,
            _num,
            _semi
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
    };
};