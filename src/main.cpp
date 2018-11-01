/**
 * @file main.cpp
 * @brief evaluate_postfix class functions
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @version 0.1
 * @date 25-10-2018
 */

/**
 * @brief Include's
 * 
 */
#include <iostream>
#include <iomanip>
#include <vector>

#include "../include/parser.h" 
#include "../include/infix2postfix.h" 
#include "../include/evaluate_postfix.h" 

/**
 * @brief Print erro msg
 * 
 * @param result The erro name
 */
void print_error_msg( const Parser::ResultType & result )
{    
    switch ( result.type )
    {
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            std::cout << "Unexpected end of expression at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::ILL_FORMED_INTEGER:
            std::cout << "Ill formed integer at column (" << result.at_col+1 << ")!\n";
            break;
        case Parser::ResultType::MISSING_TERM:
            std::cout << "Missing <term> at column (" << result.at_col+1 << ")!\n";
            break;
        case Parser::ResultType::MISSING_CLOSING_LAST:
            std::cout << "Missing closing ”)” at column (" << result.at_col+1 << ")!\n";
            break;
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            std::cout << "Extraneous symbol after valid expression found at column (" << result.at_col+1 << ")!\n";
            break;
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            std::cout << "Integer constant out of range beginning at column (" << result.at_col+1 << ")!\n";
            break;
        default:
            std::cout << "Unhandled error found!\n";
            break;
    }    
}

int main(int argc, char const *argv[])
{
    //!< Capture mathematical expressions
    std::vector < std::string > expressions;
    std::string str;
    while( getline( std::cin, str) )
    {
        expressions.push_back(str);
    }
    
    //!< Start of operations
    Parser my_parser; 
    infix2postfix expressao_incial;
    evaluate_postfix gerar_resultado;
    for( const auto & expr : expressions )
    {
        auto result = my_parser.parse( expr );        
        if ( result.type != Parser::ResultType::OK ){
            print_error_msg(result);
        }
        else {                      
            auto postfix = expressao_incial.infix_to_postfix( my_parser.get_tokens() );            
            auto result = gerar_resultado.evaluate_to_postfix( postfix );
            std::cout << result << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
