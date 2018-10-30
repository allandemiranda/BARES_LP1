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
#include <vector>    //!< std::vectork

using value_type = long int;    //!< Type we operate on.

#include "../include/infix2postfix.h" //!< Class way

bool infix2postfix::is_operator( std::string s ){
    return (std::string("*^/%+-").find( s ) != std::string::npos);
}

bool infix2postfix::is_operand( std::string s ){   
    return ((stoi(s) >= -32767) and (stoi(s) <= 32767));   
}

bool infix2postfix::is_opening_scope( std::string s ){ 
    return (s == "("); 
}

bool infix2postfix::is_closing_scope( std::string s ){ 
    return (s == ")"); 
}

bool infix2postfix::is_right_association( std::string op ){ 
    return op == "^"; 
}

value_type infix2postfix::char2integer( char c ){ 
    return c - '0'; 
}

short infix2postfix::get_precedence( std::string op ){
    std::vector <std::string> temp = {"^","*","/","%","+","-","("};
    std::vector <short> temp_num = {3,3,3,2,2,1,0};
    short flag(0);
    for(std::vector<std::string>::iterator i = temp.begin(); i<temp.end(); ++i){
        if(op == *i){
            return temp_num[flag];
        }
        flag++;
    }
    assert( false );  
    return -1;
}

bool infix2postfix::has_higher_or_eq_precedence( std::string op1 , std::string op2 ){
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

std::string infix2postfix::infix_to_postfix( std::vector <std::string> infix ){
    std::string postfix(""); //!< Conversion result    
    //!< Scroll through the entry, to process each item / token / character
    for( auto c : infix ){        
        std::cout << c << std::endl;
        //!< Operating goes straight to the exit
        if( is_operand( c ) ){
            postfix += c;
        }           
        if( is_opening_scope(c) ){
            postfix_numbers_stack.push( c ); //!< '(' enters the waiting stack on top of
        } else {
            if( is_closing_scope(c) ){
                //!< Unpack to find the corresponding opening scope
                while( not is_opening_scope( postfix_numbers_stack.top() ) ){
                    postfix += postfix_numbers_stack.top();
                    postfix_numbers_stack.pop();
                }
                postfix_numbers_stack.pop(); //!< Remember to discard the '(' which is at the top of the stack
            } else {
                if ( is_operator( c ) ){ 
                    //!< + - ^ *...        
                    //!< Perform waiting operations that are equal to or greater than
                    //!< in priority (except for the right-left association)
                    while( not postfix_numbers_stack.empty() and has_higher_or_eq_precedence( postfix_numbers_stack.top(), c ) ){ 
                        //!< s.top() >= c
                        postfix += postfix_numbers_stack.top();
                        postfix_numbers_stack.pop();
                    }
                    //!< The operation that arrives, always has to wait
                    postfix_numbers_stack.push( c );
                    }
            }
        }
        
    }

    std::stack< std::string > s; //!< Stack for help on conversion
    s = postfix_numbers_stack;
    //!< Unload the pending battery operations
    while( not s.empty() ){
        postfix += s.top();
        postfix_numbers_vector.push_back(s.top());
        s.pop();
    }

    return postfix;
}