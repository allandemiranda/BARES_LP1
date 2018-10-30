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
#include <string>    //!< std::string
#include <vector>    // std::vector
#include <stack>     // stack

using value_type = long int;    //!< Type we operate on.


#include <iostream>

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
        std::string infix_to_postfix(std::vector <std::string>);        

        std::vector < std::string > return_vector_numbers(void){     
            std::vector <std::string> temp;
            for( auto i = postfix_numbers_vector.size()-1; i>=0; --i){
                std::cout << postfix_numbers_vector[i] << std::endl;
                temp.push_back(postfix_numbers_vector[i]);
            }
            return temp;
        }


    private:      
        std::stack <std::string> postfix_numbers_stack; //!< Postfix Numbers Stack
        std::vector <std::string> postfix_numbers_vector;

        /**
         * @brief Identifies whether the std::string is a operator
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_operator( std::string );

        /**
         * @brief Identifies whether the std::string is a operand
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_operand( std::string );

        /**
         * @brief Identifies whether the std::string is a opening scope
         * 
         * @return true If it is
         * @return false if it isn't 
         */
        bool is_opening_scope( std::string );

        /**
         * @brief Identifies whether the std::string is a closing scope
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool is_closing_scope( std::string );

        /**
         * @brief Check the operand's type of association
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool is_right_association( std::string );

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
        short get_precedence( std::string );

        /**
         * @brief Determines whether the first operator is >= than the second operator
         * 
         * @return true If it is
         * @return false if it isn't
         */
        bool has_higher_or_eq_precedence( std::string , std::string );        
};

#endif