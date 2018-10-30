/**
 * @file infix2postfix.cpp
 * @brief infix2postfix class functions
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @version 0.1
 * @date 25-10-2018
 */

/**
 * @brief Aliase's and Include's
 * 
 */
#include <stack>     //!< stack
#include <string>    //!< std::string
#include <cassert>   //!< assert
#include <cmath>     //!< std::pow
#include <vector>    //!< std::vector

#include "../include/infix2postfix.h" //!< Class way

bool infix2postfix::is_operator( char s ){
    return (std::string("*^/%+-").find( s ) != std::string::npos);
}

bool infix2postfix::is_opening_scope( char s ){ 
    return (s == '('); 
}

bool infix2postfix::is_closing_scope( char s ){ 
    return (s == ')'); 
}

bool infix2postfix::is_right_association( char op ){ 
    return op == '^'; 
}

short infix2postfix::get_precedence( char op ){
    switch( op )
    {
        case '^' : return 3;
        case '*' :
        case '/' :
        case '%' : return 2;
        case '+' :
        case '-' : return 1;
        case '(' : return 0;
        default  : assert( false );  return -1;
    }
}

bool infix2postfix::has_higher_or_eq_precedence( char op1 , char op2 ){
    //!< Takes the numerical values corresponding to the precedences
    int p_op1 = get_precedence( op1 );
    int p_op2 = get_precedence( op2 );

    if ( p_op1 > p_op2 ){
        return true;
    } else {
        if ( p_op1 < p_op2 ){
            return false;
        } else { 
            //!< p_op1 == p_op2            
            if ( is_right_association( op1 ) ){
                return false; //!< If the association is right-left
            }            
            return true; //!< Normal rule
        }
    }
}

std::vector <symbol> infix2postfix::infix_to_postfix( std::vector <symbol> infix ){
    std::vector <symbol> postfix; //!< Conversion result
    std::stack< symbol > s; //!< Stack for help on conversion
    //!< Scroll through the entry, to process each item / token / character
    for( symbol c : infix ){        
        //!< Operating goes straight to the exit
        if(c.type == Token::token_t::OPERAND){
            postfix.push_back(Token(c.value,Token::token_t::OPERAND));
        } else {
            if( is_opening_scope(c.value[0])){
                s.push( Token(c.value, Token::token_t::CLOSING) ); //!< '(' enters the waiting stack on top of
            } else {
                if( is_closing_scope(c.value[0] )){
                    //!< Unpack to find the corresponding opening scope
                    while( not is_opening_scope( s.top().value[0] ) ){
                        postfix.push_back(Token(s.top().value, Token::token_t::CLOSING));
                        s.pop();
                    }
                    s.pop(); //!< Remember to discard the '(' which is at the top of the stack
                } else {
                    if ( is_operator( c.value[0] ) ){ 
                        //!< + - ^ *...        
                        //!< Perform waiting operations that are equal to or greater than
                        //!< in priority (except for the right-left association)
                        while( not s.empty() and has_higher_or_eq_precedence( s.top().value[0], c.value[0] ) ){ 
                            //!< s.top() >= c
                            postfix.push_back(Token(s.top().value,Token::token_t::OPERATOR));
                            s.pop();
                        }
                        //!< The operation that arrives, always has to wait
                        s.push( Token(c.value, Token::token_t::OPERATOR) );
                     }
                }
            }
        }
    }

    //!< Unload the pending battery operations
    while(!s.empty()){      
        postfix.push_back(Token(s.top().value,Token::token_t::OPERATOR));
        s.pop();
    }

    return postfix;
}