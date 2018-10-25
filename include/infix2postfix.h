/**
 * @file infix2postfix.h
 * @author Allan de Miranda - Josoé Cláudio (allandemiranda@gmail.com josoeclaudiox@gmail.com)
 * @brief Classe para converter o vetor de caracteres infix para postfix
 * @version 0.1
 * @date 25-10-2018
 */

#ifndef _INFIX2POSTFIX_H_
#define _INFIX2POSTFIX_H_

#include <string>
#include <vector>

/**
 * @brief Class
 * 
 */
class infix2postfix{
    private:
        std::vector <std::string> infix;
    public:
        infix2postfix(std::vector <std::string>);
};

#endif