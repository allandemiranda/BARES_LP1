/**
 * @file infix2postfix.h
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @version 0.1
 * @date 25-10-2018
 */

#ifndef _INFIX2POSTFIX_H_
#define _INFIX2POSTFIX_H_

//=== Aliases
using value_type = long int; //!< Type we operate on.
using symbol = char; //!< A symbol in this implementation is just a char.

#include <string>

/**
 * @brief Class
 * 
 */
class infix2postfix{
    public:
        // Converção
        std::string infix_to_postfix(std::string); 

    private:
        // Simple helper functions that identify the incoming symbol.
        bool is_operator( symbol );
        bool is_operand( symbol );
        bool is_opening_scope( symbol );
        bool is_closing_scope( symbol );

        /// Check the operand's type of association.
        bool is_right_association( symbol );

        /// Converts a char (1-digit operand) into an integer.
        value_type char2integer( char );

        /// Returns the precedence value (number) associated with an operator.
        short get_precedence( symbol );

        /// Determines whether the first operator is >= than the second operator.
        bool has_higher_or_eq_precedence( symbol , symbol );        
};

#endif