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
using value_type = long int;    //!< Type we operate on.
using symbol = char;            //!< A symbol in this implementation is just a char.

#include <string>    //!< std::string
#include <stack>     //!< stack

/**
 * @brief Class for infix expression to postfix
 * 
 */
class infix2postfix{
    public:
        /**
         * @brief To do the conversion
         * 
         * @return std::string String converted
         */
        std::string infix_to_postfix(std::string); 

        symbol top_and_pop_postfix_numbers(void){
            symbol c = postfix_numbers.top();
            postfix_numbers.pop();
            return c;
        }

        value_type size_postfix_numbers(void){
            return postfix_numbers.size();
        }

    private:      
        std::stack< symbol > postfix_numbers; //!< POstfix Numbers

        /**
         * @brief Identifies whether the symbol is a operator
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_operator( symbol );

        /**
         * @brief Identifies whether the symbol is a operand
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_operand( symbol );

        /**
         * @brief Identifies whether the symbol is a opening scope
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_opening_scope( symbol );

        /**
         * @brief Identifies whether the symbol is a closing scope
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool is_closing_scope( symbol );

        /**
         * @brief Check the operand's type of association
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool is_right_association( symbol );

        /**
         * @brief Converts a char (1-digit operand) into an integer
         * 
         * @return value_type The converted
         */
        value_type char2integer( char );

        /**
         * @brief Get the precedence object
         * 
         * @return short The precedence value (number) associated with an operator
         */
        short get_precedence( symbol );

        /**
         * @brief Determines whether the first operator is >= than the second operator
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool has_higher_or_eq_precedence( symbol , symbol );        
};

#endif