#include <iostream>

namespace Jam {
    namespace Error {
        template<typename... Ts>
        void CallError(Ts&&... ts) {
            std::cerr << "\x1B[1m\x1B[38;2;255;51;51mError\x1B[0m\x1B[22m: ";
            (..., ([&ts] {
                std::cerr << ts ;
            })());
            std::cerr << "\n";
            std::exit(EXIT_FAILURE);
        }

        template<typename... Ts>
        void CallWarning(Ts&&... ts) {
            (..., ([&ts] {
                std::cerr << "\x1B[1m\x1B[38;2;255;204;0mWarning\x1B[0m\x1B[22m: " << ts << '\n';
            })());
            std::exit(EXIT_FAILURE);
        }
    };
};