/**
 * @file infix2postfix.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2018-10-29
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <stack>     // stack
#include <string>    // string
#include <cassert>   // assert
#include <cmath>     // pow
#include <vector>    // std::vector

//=== Aliases ++++++++++++++++  ACHO QUER PODE TIRAR ESSES USING !
using value_type = long int; //!< Type we operate on.
using symbol = char; //!< A symbol in this implementation is just a char.

#include "../include/infix2postfix.h"

// Simple helper functions that identify the incoming symbol.
bool infix2postfix::is_operator( symbol s )
{
    return std::string("*^/%+-").find( s ) != std::string::npos;
}

bool infix2postfix::is_operand( symbol s )
{   return s >= '0' and s <= '9';   }

bool infix2postfix::is_opening_scope( symbol s )
{ return s == '('; }

bool infix2postfix::is_closing_scope( symbol s )
{ return s == ')'; }

/// Check the operand's type of association.
bool infix2postfix::is_right_association( symbol op )
{ return op == '^'; }

/// Converts a char (1-digit operand) into an integer.
value_type infix2postfix::char2integer( char c )
{ return c - '0'; }

/// Returns the precedence value (number) associated with an operator.
short infix2postfix::get_precedence( symbol op )
{
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

/// Determines whether the first operator is >= than the second operator.
bool infix2postfix::has_higher_or_eq_precedence( symbol op1 , symbol op2 )
{
    // pega os valores numericos correspondentes aas precedencias.
    int p_op1 = get_precedence( op1 );
    int p_op2 = get_precedence( op2 );

    if ( p_op1 > p_op2 )
    {
        return true;
    }
    else if ( p_op1 < p_op2 )
    {
        return false;
    }
    else // p_op1 == p_op2 
    {
        // exceção a regra, que acontece com associacao direita-esquerda.
        if ( is_right_association( op1 ) ) return false;
        // regra normal.
        return true;
    }
}

/// Converts a expression in infix notation to a corresponding profix representation.
std::string infix2postfix::infix_to_postfix( std::string infix )
{
    std::string postfix(""); // resultado da conversao.
    std::stack< symbol > s; // pilha de ajuda na conversao.

    // Percorrer a entrada, para processar cada item/token/caractere
    for( auto c : infix )
    {        
        // Operando vai direto pra saida.
        if( is_operand( c ) )
            postfix += c;
        else if( is_opening_scope(c) )
            s.push( c ); // '(' entra na pilha de espera em cima de quem estiver por la.
        else if( is_closing_scope(c) )
        {
            // desempilhe ateh achar o escopo de abertura correspondente.
            while( not is_opening_scope( s.top() ) )
            {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // Lembre de descartar o '(' que estah no topo da pilha.
        }
        else if ( is_operator( c ) ) // + - ^ *...
        {
            // Desempilhar as operaçoes em espera que são iguais ou superiores
            // em prioridade (com excecao da associacao direita-esquerda).
            while( not s.empty() and has_higher_or_eq_precedence( s.top(), c ) ) // s.top() >= c
            {
                postfix += s.top();
                s.pop();
            }

            // A operacao que chegar, sempre tem que esperar.
            s.push( c );
        }
    }

    // Lembre-se de descarregar as operacoes pendentes da pilha.
    while( not s.empty() )
    {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}