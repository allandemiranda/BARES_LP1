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
#include <stack>     //!< stack
#include <string>    //!< string
#include <cassert>   //!< assert
#include <cmath>     //!< pow
#include <stdexcept> //!< std::runtime_error
#include <vector>    //!< std::vector

#include "../include/evaluate_postfix.h" //!< Class way

bool evaluate_postfix::is_operator( std::string s ){
    return std::string("*^/%+-").find( s ) != std::string::npos;
}

std::string evaluate_postfix::execute_operator( value_type v1, value_type v2, const char op ){
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

std::string evaluate_postfix::evaluate_to_postfix( std::vector <symbol> postfix ){
    std::stack< value_type > s;
    
    for( symbol c : postfix ){
        if(c.type == Token::token_t::OPERAND){
            s.push(  stoll(c.value) );
        } else {
            if ( is_operator( c.value ) ){
                value_type op2 = s.top(); s.pop();
                value_type op1 = s.top(); s.pop();
                auto result = execute_operator( op1, op2, c.value[0] ); // ( 2, 9, '*' )
                if(result == ( "Division by zero!" )){
                    return result;
                }
                s.push( stoll(result) );
            } else {
                assert( false );
            }
        }
    }

    //!< Cheking if have numeric overflow
    value_type total = s.top();
    if((total > 32767) or (total < -32767)){
        return ( "Numeric overflow error!" );
    }

    return std::to_string(total);
}