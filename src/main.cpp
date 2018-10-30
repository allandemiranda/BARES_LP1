/**
 * @file main.cpp
 * @brief evaluate_postfix class functions
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @version 0.1
 * @date 25-10-2018
 */

#include <iostream>
#include <iomanip>
#include <vector>

#include "../include/parser.h" 

// Class's criadas por Allan
#include "../include/infix2postfix.h" 
#include "../include/evaluate_postfix.h" 

// FAZER A PARTE QUE LER O ARQUIVO
std::vector < std::string > expressions = 
{
    "1 - 2",
    "2+",
    "3 * d",
    "2 = 3",
    "2.3 + 4",
    "2 * 3 4",
    "2 ** 3",
    "%5 * 10",
    "*5 * 10",
    "(2+3)*/(1-4)",
    "(-3*4)(10*5)",
    "2 - 4)",
    "2) - 4",
    ")2 - 4",
    "((2%3) * 8",
    "3/(1-1)",
    "10/(3*3^-2)",
    "20*20000"
};


void print_error_msg( const Parser::ResultType & result )
{    
    switch ( result.type )
    {
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            std::cout << " Unexpected end of expression at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::ILL_FORMED_INTEGER:
            std::cout << " Ill formed integer at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::MISSING_TERM:
            std::cout << " Missing <term> at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::MISSING_CLOSING_LAST:
            std::cout << " Missing closing ”)”at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            std::cout << " Extraneous symbol after valid expression found at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            std::cout << " Integer constant out of range beginning at column (" << result.at_col << ")!\n";
            break;
        default:
            std::cout << " Unhandled error found!\n";
            break;
    }    
}


int main(void)
{
    Parser my_parser; 
    infix2postfix expressao_incial;
    evaluate_postfix gerar_resultado;
    for( const auto & expr : expressions )
    {
        auto result = my_parser.parse( expr );
        std::cout << std::setw(20) <<  std::left << expr;
        if ( result.type != Parser::ResultType::OK )
            print_error_msg(result);
        else
        {            
            auto postfix = expressao_incial.infix_to_postfix( expr );
            auto result = gerar_resultado.evaluate_to_postfix( postfix );
            std::cout << " " << result << std::endl;
        }         
    }

    return EXIT_SUCCESS;
}
