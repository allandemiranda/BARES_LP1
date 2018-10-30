/**
 * @file evaluate_postfix.cpp
 * @brief evaluate_postfix class functions
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @version 0.1
 * @date 25-10-2018
 */

/**
 * @brief Aliase's and Include's
 * 
 */
using value_type = long int;    //!< Type we operate on.
using symbol = char;            //!< A symbol in this implementation is just a char.

#include <stack>     //!< stack
#include <string>    //!< string
#include <cassert>   //!< assert
#include <cmath>     //!< pow
#include <stdexcept> //!< std::runtime_error
#include <vector>    //!< std::vector

#include "../include/evaluate_postfix.h" //!< Class way

value_type evaluate_postfix::char2integer( char c ){ 
    return c - '0'; 
}

bool evaluate_postfix::is_operand( symbol s ){   
    return s >= '0' and s <= '9';   
}

bool evaluate_postfix::is_operator( symbol s ){
    return std::string("*^/%+-").find( s ) != std::string::npos;
}

std::string evaluate_postfix::execute_operator( value_type v1, value_type v2, symbol op ){
    switch( op )
    {
        case '^':  return std::to_string(pow( v1,v2 ));
        case '*':  return std::to_string(v1*v2);
        case '/':  if ( v2 == 0 ) return ( "Division by zero!" );
                   return std::to_string(v1/v2);
        case '%':  if ( v2 == 0 ) return ( "Division by zero!" );
                   return std::to_string(v1%v2);
        case '+':  return std::to_string(v1+v2);
        case '-':  return std::to_string(v1-v2);
        default:   throw std::runtime_error( "ERRO FATAL" );
    }
}

std::string evaluate_postfix::evaluate_to_postfix( std::string postfix ){
    std::stack< value_type > s;

    for( auto c : postfix ){
        if ( is_operand( c ) ){
            s.push( char2integer( c ) );
        } else {
            if ( is_operator( c ) ){
                value_type op2 = s.top(); s.pop();
                value_type op1 = s.top(); s.pop();
                auto result = execute_operator( op1, op2, c ); // ( 2, 9, '*' )
                if(result == ( "Division by zero!" )){
                    return result;
                }
                s.push( stoi(result) );
            } else {
                assert( false );
            }
        }
    }

    //!< Cheking if have numeric overflow
    long int total = s.top();
    if((total > 32767) or (total < -32767)){
        return ( "Numeric overflow error!" );
    }

    return std::to_string(total);
}