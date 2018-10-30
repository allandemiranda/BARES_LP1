/**
 * @file evaluate_postfix.h
 * @brief File containing the class that will show the total
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @version 0.1
 * @date 25-10-2018
 */

#ifndef _EVALUATE_POSTFIX_H_
#define _EVALUATE_POSTFIX_H_

/**
 * @brief Aliase's and Include's
 * 
 */
using value_type = long int;    //!< Type we operate on.
using symbol = Token;           //!< A symbol in this implementation is just a token.

#include <string> //!< std::string.

class evaluate_postfix
{
    public:
        /**
         * @brief Change an infix expression into its corresponding postfix representation
         * 
         * @return value_type The total
         */
        std::string evaluate_to_postfix( std::vector <symbol> );
        
    private:
        /// Converts a char (1-digit operand) into an integer.

        /**
         * @brief Converts a char (1-digit operand) into an integer
         * 
         * @return value_type The converted
         */
        value_type char2integer( char );

        /**
         * @brief Identifies whether the symbol is a operand
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_operand( symbol );

        /**
         * @brief Identifies whether the symbol is a operator
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_operator( symbol );

        /**
         * @brief Execute the binary operator on two operands and return the result
         * 
         * @return value_type The result
         */
        std::string execute_operator( value_type, value_type, symbol);  
};

#endif