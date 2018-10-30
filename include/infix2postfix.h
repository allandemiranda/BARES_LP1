/**
 * @file infix2postfix.h
 * @brief File containing the class that will convert the mathematical operations
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @version 0.1
 * @date 25-10-2018
 */

#ifndef _INFIX2POSTFIX_H_
#define _INFIX2POSTFIX_H_

/**
 * @brief Aliase's and Include's
 * 
 */
#include <string> //!< std::string
#include <vector> //!< std::vector
#include "../include/token.h" //!< Class way

using value_type = long int;    //!< Type we operate on.
using symbol = Token;           //!< A symbol in this implementation is just a token.

/**
 * @brief Class for infix expression to postfix
 * 
 */
class infix2postfix{
    public:
        /**
         * @brief To do the conversion
         * 
         * @return std::vector String converted
         */
        std::vector <symbol> infix_to_postfix(std::vector <symbol>); 

    private:        
        /**
         * @brief Identifies whether the char is a operator
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_operator( const char );

        // /**
        //  * @brief Identifies whether the char is a operand
        //  * 
        //  * @return true If it is
        //  * @return false if it isn't 
        //  */
        // bool is_operand( char );

        /**
         * @brief Identifies whether the char is a opening scope
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_opening_scope( const char );

        /**
         * @brief Identifies whether the char is a closing scope
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool is_closing_scope( const char );

        /**
         * @brief Check the operand's type of association
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool is_right_association( const char );

        /**
         * @brief Converts a char (1-digit operand) into an integer
         * 
         * @return value_type The converted
         */
        // value_type char2integer( char );

        /**
         * @brief Get the precedence object
         * 
         * @return short The precedence value (number) associated with an operator
         */
        short get_precedence( const char );

        /**
         * @brief Determines whether the first operator is >= than the second operator
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool has_higher_or_eq_precedence( const char , const char );        
};

#endif