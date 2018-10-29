#include <iostream>  // cout, endl
#include <stack>     // stack
#include <string>    // string
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error
#include <vector>    // std::vector

#include "infix2postfix.cpp" // -----> ISSO AQUI ACHO QUE APAGA
#include "evaluate_postfix.cpp" // -----> ISSO AQUI ACHO QUE APAGA

//=== Aliases
using value_type = long int; //!< Type we operate on.
using symbol = char; //!< A symbol in this implementation is just a char.

int main( void )
{
    // Class
    infix2postfix expressao_incial;
    evaluate_postfix gerar_resultado;


    // A expression is a queue of sysmbols (chars).
    std::vector< std::string > exps {
        "4/(5^2)+(6^2^3)",
        "1+ 3 * ( 4 + 8 * 3 ^7)",
        "2*2*3",
        "2^2^3" } ;

    for ( const auto& e : exps )
    {
        auto postfix = expressao_incial.infix_to_postfix( e );
        std::cout << ">>> Input (infix)    = " << e << "\n";
        std::cout << ">>> Output (postfix) = " << postfix << "\n";

        auto result = gerar_resultado.evaluate_to_postfix( postfix );
        std::cout << ">>> Result is: " << result << std::endl;
    }

    std::cout << "\n>>> Normal exiting...\n";
    return EXIT_SUCCESS;
}