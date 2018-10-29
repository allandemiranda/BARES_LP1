/**
 * @file evaluate_postfix.h
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @version 0.1
 * @date 25-10-2018
 */
#ifndef _EVALUATE_POSTFIX_H_
#define _EVALUATE_POSTFIX_H_

#include <string>    // string

//=== Aliases
using value_type = long int; //!< Type we operate on.
using symbol = char; //!< A symbol in this implementation is just a char.

class evaluate_postfix
{
    public:
        /// Change an infix expression into its corresponding postfix representation.
        value_type evaluate_to_postfix( std::string );
        
    private:
        /// Converts a char (1-digit operand) into an integer.
        value_type char2integer( char );

        // Simple helper functions that identify the incoming symbol.
        bool is_operand( symbol );
        bool is_operator( symbol s );

        /// Execute the binary operator on two operands and return the result.
        value_type execute_operator( value_type, value_type, symbol);  
};

#endif