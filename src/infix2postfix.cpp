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
using value_type = long int;    //!< Type we operate on.
using symbol = char;            //!< A symbol in this implementation is just a char.

#include <stack>     //!< stack
#include <string>    //!< std::string
#include <cassert>   //!< assert
#include <cmath>     //!< std::pow
#include <vector>    //!< std::vector

#include "../include/infix2postfix.h" //!< Class way

bool infix2postfix::is_operator( symbol s ){
    return (std::string("*^/%+-").find( s ) != std::string::npos);
}

bool infix2postfix::is_operand( symbol s ){   
    return (s >= '0' and s <= '9');   
}

bool infix2postfix::is_opening_scope( symbol s ){ 
    return (s == '('); 
}

bool infix2postfix::is_closing_scope( symbol s ){ 
    return (s == ')'); 
}

bool infix2postfix::is_right_association( symbol op ){ 
    return op == '^'; 
}

value_type infix2postfix::char2integer( char c ){ 
    return c - '0'; 
}

short infix2postfix::get_precedence( symbol op ){
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

bool infix2postfix::has_higher_or_eq_precedence( symbol op1 , symbol op2 ){
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

std::string infix2postfix::infix_to_postfix( std::string infix ){
    std::string postfix(""); //!< Conversion result
    std::stack< symbol > s; //!< Stack for help on conversion
    //!< Scroll through the entry, to process each item / token / character
    for( auto c : infix ){        
        //!< Operating goes straight to the exit
        if( is_operand( c ) ){
            postfix += c;
        } else {
            if( is_opening_scope(c) ){
                s.push( c ); //!< '(' enters the waiting stack on top of
            } else {
                if( is_closing_scope(c) ){
                    //!< Unpack to find the corresponding opening scope
                    while( not is_opening_scope( s.top() ) ){
                        postfix += s.top();
                        s.pop();
                    }
                    s.pop(); //!< Remember to discard the '(' which is at the top of the stack
                } else {
                    if ( is_operator( c ) ){ 
                        //!< + - ^ *...        
                        //!< Perform waiting operations that are equal to or greater than
                        //!< in priority (except for the right-left association)
                        while( not s.empty() and has_higher_or_eq_precedence( s.top(), c ) ){ 
                            //!< s.top() >= c
                            postfix += s.top();
                            s.pop();
                        }
                        //!< The operation that arrives, always has to wait
                        s.push( c );
                     }
                }
            }
        }
    }

    //!< Unload the pending battery operations
    while( not s.empty() ){
        postfix += s.top();
        s.pop();
    }

    return postfix;
}