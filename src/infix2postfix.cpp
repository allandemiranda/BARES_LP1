/**
 * @file infix2postfix.cpp
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @brief 
 * @version 0.1
 * @date 25-10-2018
 * 
 * 
 */

#include "../include/infix2postfix.h" // Class

/**
 * @brief Construct a new infix2postfix::infix2postfix object
 * 
 * @param _new_string 
 */
infix2postfix::infix2postfix(std::vector <std::string> _new_string){
    for(std::string i : _new_string){
        infix.push_back(i);
    }
}

