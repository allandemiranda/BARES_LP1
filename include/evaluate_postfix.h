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
#include <string> //!< std::string.
#include "../include/token.h" //!< Class way

using value_type = long int;    //!< Type we operate on.
using symbol = Token;           //!< A symbol in this implementation is just a token.

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
        // value_type char2integer( char );

        /**
         * @brief Identifies whether the char is a operand
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        // bool is_operand( const char );

        /**
         * @brief Identifies whether the char is a operator
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_operator( std::string );

        /**
         * @brief Execute the binary operator on two operands and return the result
         * 
         * @return value_type The result
         */
        std::string execute_operator( value_type, value_type, const char);  
};

#endif