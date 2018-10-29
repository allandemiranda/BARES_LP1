#include <stack>     // stack
#include <string>    // string
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error
#include <vector>    // std::vector

//=== Aliases
using value_type = long int; //!< Type we operate on.
using symbol = char; //!< A symbol in this implementation is just a char.

#include "../include/evaluate_postfix.h"

/// Converts a char (1-digit operand) into an integer.
value_type evaluate_postfix::char2integer( char c )
{ return c - '0'; }

// Simple helper functions that identify the incoming symbol.
bool evaluate_postfix::is_operand( symbol s )
{   return s >= '0' and s <= '9';   }

bool evaluate_postfix::is_operator( symbol s )
{
    return std::string("*^/%+-").find( s ) != std::string::npos;
}

/// Execute the binary operator on two operands and return the result.
value_type evaluate_postfix::execute_operator( value_type v1, value_type v2, symbol op )
{
    switch( op )
    {
        case '^':  return pow( v1,v2 );
        case '*':  return v1*v2;
        case '/':  if ( v2 == 0 ) throw std::runtime_error( "divisao por zero" );
                   return v1/v2;
        case '%':  if ( v2 == 0 ) throw std::runtime_error( "divisao por zero" );
                   return v1%v2;
        case '+': return v1+v2;
        case '-': return v1-v2;
        default: throw std::runtime_error( "undefined operator" );
    }
}

/// Change an infix expression into its corresponding postfix representation.
value_type evaluate_postfix::evaluate_to_postfix( std::string postfix )
{
    std::stack< value_type > s;

    for( auto c : postfix )
    {
        if ( is_operand( c ) )
            s.push( char2integer( c ) );
        else if ( is_operator( c ) )
        {
            value_type op2 = s.top(); s.pop();
            value_type op1 = s.top(); s.pop();
            auto result = execute_operator( op1, op2, c ); // ( 2, 9, '*' )
            s.push( result );
        }
        else assert( false );
    }

    return s.top();
}