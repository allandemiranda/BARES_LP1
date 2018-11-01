#include "../include/parser.h"
#include <iterator>
#include <algorithm>

/// Converts the input character c_ into its corresponding terminal symbol code.
Parser::terminal_symbol_t  Parser::lexer( char c_ ) const
{
    switch( c_ )
    {
        case '+':  return terminal_symbol_t::TS_PLUS;
        case '-':  return terminal_symbol_t::TS_MINUS;
        case '*':  return terminal_symbol_t::TS_TIMES;
        case '/':  return terminal_symbol_t::TS_DIVISION;
        case '%':  return terminal_symbol_t::TS_MODULUS;
        case '^':  return terminal_symbol_t::TS_POWER;
        // case '(':  return terminal_symbol_t::TS_CLOSING_FIRST;
        // case ')':  return terminal_symbol_t::TS_CLOSING_LAST;
        case ' ':  return terminal_symbol_t::TS_WS;
        case   9:  return terminal_symbol_t::TS_TAB;
        case '0':  return terminal_symbol_t::TS_ZERO;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':  return terminal_symbol_t::TS_NON_ZERO_DIGIT;
        case '\0': return terminal_symbol_t::TS_EOS; // end of string: the $ terminal symbol
    }
    return terminal_symbol_t::TS_INVALID;
}

Parser::delimiter  Parser::d_lexer( char c_ ) const
{
    switch( c_ )
    {
        case '(':  return delimiter::DE_CLOSING_FIRST;
        case ')':  return delimiter::DE_CLOSING_LAST;
        case '\0': return delimiter::DE_EOS; // end of string: the $ terminal symbol
    }
    return delimiter::DE_INVALID;
}

/// Consumes a valid character from the input source expression.
void Parser::next_symbol( void )
{
    // Advances iterator to the next valid symbol for processing
    // std::advance( m_it_curr_symb, 1 );
    m_it_curr_symb++;
}

/// Checks whether we reached the end of the input expression string.
bool Parser::end_input( void ) const
{
    // "Fim de entrada" ocorre quando o iterador chega ao
    // fim da string que guarda a expressão.
    return m_it_curr_symb == m_expr.end();
}

#ifdef PEEK
// Returns the result of trying to match the current character with c_, **without** consuming the current character from the input expression.
bool Parser::peek( terminal_symbol_t c_ ) const
{
    // Checks whether the input symbol is equal to the argument symbol.
    return ( not end_input() and
             lexer( *m_it_curr_symb ) == c_ );
}
#endif

/// Returns the result of trying to match and consume the current character with c_.
/*!
 * If the match is not successful, the current character (from the input) **is not consumed**.
 * @param c_ the current character from the input source expression we wish to parse.
 * @see peek().
 * @return true if we got a successful match; false otherwise.
 */
bool Parser::accept( terminal_symbol_t c_ )
{
    // If we have a match, we consume the character from the input source expression.
    // caractere da entrada.
    if ( not end_input() and
             lexer( *m_it_curr_symb ) == c_  )
    {
        next_symbol();
        
        return true;
    }
    
    return false;
}

bool Parser::d_accept( delimiter c_ )
{
    // If we have a match, we consume the character from the input source expression.
    // caractere da entrada.
    
    if ( not end_input() and d_lexer( *m_it_curr_symb ) == c_  )
    {
        next_symbol();
        return true;
    }

    return false;
}

#ifdef EXPECT
// Skips all white spaces and tries to accept() the next valid character. @see accept().
bool Parser::expect( terminal_symbol_t c_ )
{
    // Skip all white spaces first.
    skip_ws();
    return accept( c_ );
}
#endif


/// Ignores any white space or tabs in the expression until reach a valid character or end of input.
void Parser::skip_ws( void )
{
    // Skip white spaces, while at the same time, check for end of string.
    while ( not end_input() and std::isspace( *m_it_curr_symb ) )
            //( lexer( *m_it_curr_symb ) == Parser::terminal_symbol_t::TS_WS  or
            //  lexer( *m_it_curr_symb ) == Parser::terminal_symbol_t::TS_TAB ) )
    {
        next_symbol();
    }
}

void Parser::skip_u_minus()
{
    minusCount = 0;
    
    for ( /* empty */ ; not end_input() and *(m_it_curr_symb) == '-' and *(m_it_curr_symb+1) == '-'; ++minusCount )
    { 
        // m_it_curr_symb++;
        next_symbol();
    }
    
    if( minusCount % 2 == 0 )
    {
        minus = '+';
    }
    else
    {
        minus = '-';
    }    
}

void Parser::skip_closing()
{
    auto i( (m_it_curr_symb) );
    while( not end_input() /* and (*m_it_curr_symb == '(' */ or *m_it_curr_symb == ')' )
    {
        // if( *m_it_curr_symb == '(' )
        // {
        //     m_tk_list.emplace_back( Token( "(", Token::token_t::CLOSING ) );
        //     m_result.type = ResultType::OK;
        //     next_symbol();
        // }
        // else if( *m_it_curr_symb == ')' )
        // {
        //     m_tk_list.emplace_back( Token( ")", Token::token_t::CLOSING ) );
        //     m_result.type = ResultType::OK;
        //     next_symbol();
        // }
        // next_symbol();
        ++i;
        // if( or *m_it_curr_symb == ')' )
    }
} 



//=== Non Terminal Symbols (NTS) methods.

/// Validates (i.e. returns true or false) and consumes an **expression** from the input expression string.
/*! This method parses a valid expression from the input and, at the same time, it tokenizes its components.
 *
 * Production rule is:
 * ```
 *  <expr> := <term>,{ ("+"|"-"),<term> };
 * ```
 * An expression might be just a term or one or more terms with '+'/'-' between them.
 */
bool Parser::expression()
{
    skip_ws();
    
    term();

    if( *m_it_curr_symb == '-' and *(m_it_curr_symb-1) == '-' and *(m_it_curr_symb+1) == ' ' )
    {
        m_result = ResultType( ResultType::ILL_FORMED_INTEGER, 
                                std::distance( m_expr.begin(), m_it_curr_symb ) );
        // return false;
    }
    
    closing_first_Count = 0;
    closing_last_Count = 0;
    // Process terms
    // std::cout << m_result.type << std::endl;
    while( m_result.type == ResultType::OK /*or ( *m_it_curr_symb == '(' or *m_it_curr_symb == ')' ) */)
    {
        skip_ws();
        // std::cout << m_result.type << std::endl;

        if ( accept( Parser::terminal_symbol_t::TS_PLUS ) )
        {
            // Stores the "+" token in the list.
            m_tk_list.emplace_back( Token( "+", Token::token_t::OPERATOR ) );
        }
        else if ( accept( Parser::terminal_symbol_t::TS_MINUS ) )
        {
            // Stores the "-" token in the list.
            if( minus != '-')
            {
                m_tk_list.emplace_back( Token( "-", Token::token_t::OPERATOR ) );
                // next_symbol();
            }
            // else
            // {
            //     m_result.type = ResultType::ILL_FORMED_INTEGER;
            // }
        }
        else if ( accept( Parser::terminal_symbol_t::TS_TIMES ) )
        {
            // Stores the "*" token in the list.
            m_tk_list.emplace_back( Token( "*", Token::token_t::OPERATOR ) );
        }
        else if ( accept( Parser::terminal_symbol_t::TS_DIVISION ) )
        {
            // Stores the "/" token in the list.
            m_tk_list.emplace_back( Token( "/", Token::token_t::OPERATOR ) );
        }
        else if ( accept( Parser::terminal_symbol_t::TS_MODULUS ) )
        {
            // Stores the "%" token in the list.
            m_tk_list.emplace_back( Token( "%", Token::token_t::OPERATOR ) );
        }
        else if ( accept( Parser::terminal_symbol_t::TS_POWER ) )
        {
            // Stores the "^" token in the list.
            m_tk_list.emplace_back( Token( "^", Token::token_t::OPERATOR ) );
        }
        else if ( d_accept( Parser::delimiter::DE_CLOSING_FIRST ) )
        {
            // Stores the "(" token in the list.
            if( not end_input() and *(m_it_curr_symb+1) == ')' )
            {
                m_result = ResultType( ResultType::ILL_FORMED_INTEGER, 
                                std::distance( m_expr.begin(), m_it_curr_symb ) );
                break;
            }
            // else if( std::string("0123456789").find( *(m_it_curr_symb)-1 ) != std::string::npos )
            // {
            //     m_result = ResultType( ResultType::ILL_FORMED_INTEGER, 
            //                     std::distance( m_expr.begin(), m_it_curr_symb ) );
            //     break;
            // }
            
            
            // else
            // {
                m_tk_list.emplace_back( Token( "(", Token::token_t::CLOSING ) );
                ++closing_first_Count;
            // }
        }
        else if ( d_accept( Parser::delimiter::DE_CLOSING_LAST ) )
        {
            // Stores the ")" token in the list.
            if( closing_first_Count == 0 or ( m_tk_list.back().type == Token::token_t::OPERATOR and closing_last_Count < closing_first_Count ) )
            {
                m_result = ResultType( ResultType::EXTRANEOUS_SYMBOL, 
                                std::distance( m_expr.begin(), m_it_curr_symb ) );
                break;
            }
            skip_ws();
            if( *(m_it_curr_symb) == '(' )
            {
                m_result = ResultType( ResultType::EXTRANEOUS_SYMBOL, 
                            std::distance( m_expr.begin(), m_it_curr_symb ) );
                return false;
            } 
            // else 
            // {
                m_tk_list.emplace_back( Token( ")", Token::token_t::CLOSING ) );
                ++closing_last_Count;
            // }
            
        }
        else break;

        if( end_input() and closing_last_Count < closing_first_Count )
        {
            m_result = ResultType( ResultType::MISSING_CLOSING_LAST, std::distance( m_expr.begin(), m_it_curr_symb ) );
            return true;
        }
        
        if( end_input() and ( std::string("*/^%+-(").find( *m_it_curr_symb ) == std::string::npos) )
        {
            m_result =  ResultType( ResultType::ILL_FORMED_INTEGER, 
                    std::distance( m_expr.begin(), m_it_curr_symb ) ) ;
        }
        // After either "+-*/%^" we expect a valid term, otherwise we have a missing term.
        // However, we may get a "false" term() if we got a number out of range.
        // So, we only change the error code if this is not that case (out of range).
        if ( not term() and m_result.type == ResultType::ILL_FORMED_INTEGER )
        {
            // Make the error more specific.
            if( *(m_it_curr_symb-1) != '(' and *(m_it_curr_symb-1) != ')' and *m_it_curr_symb != '(' and *m_it_curr_symb != ')' )
                m_result.type = ResultType::MISSING_TERM;
            else
                m_result.type = ResultType::OK;
        }
    }
    
    return m_result.type == ResultType::OK;
}

/// Validates (i.e. returns true or false) and consumes a **term** from the input expression string.
/*! This method parses and tokenizes a valid term from the input.
 *
 * Production rule is:
 * ```
 *  <term> := <integer>;
 * ```
 * A term is made of a single integer.
 *
 * @return true if a term has been successfuly parsed from the input; false otherwise.
 */
bool Parser::term()
{
    skip_ws();
    if( m_it_curr_symb == m_expr.begin() and (*m_it_curr_symb == '-' and *(m_it_curr_symb+1) == ' ') )
    {
        m_result.type = ResultType::ILL_FORMED_INTEGER;
        m_result.at_col = std::distance( m_expr.begin(), m_it_curr_symb );
        return false;
    }
    skip_u_minus();
    
    skip_ws();
    
    // Guarda o início do termo no input, para possíveis mensagens de erro.
    auto begin_token( m_it_curr_symb );
    // std::cout << *m_it_curr_symb << std::endl;
    // Vamos tokenizar o inteiro, se ele for bem formado.
    if( minus == '+' )
    {
        if ( integer() )
        {
            /// erros do tipo 2 ( 2 + 2 )
            ///                ^
            skip_ws();
            if( *(m_it_curr_symb) == '(' )
            {
                m_result = ResultType( ResultType::EXTRANEOUS_SYMBOL, 
                                std::distance( m_expr.begin(), m_it_curr_symb ) );
                                return false;
            }
            // Copiar a substring correspondente para uma variável string.
            std::string token_str;
            std::copy( begin_token, m_it_curr_symb, std::back_inserter( token_str ) );
            // Tentar realizar a conversão de string para inteiro (usar stoll()).
            // input_int_type token_int;
            // try { token_int = stoll( token_str ); }
            // catch( const std::invalid_argument & e )
            // {
            //     m_result = ResultType( ResultType::ILL_FORMED_INTEGER,
            //                        std::distance( m_expr.begin(), begin_token ) );
            //     return false;
            // }
            input_int_type token_int = stoll( token_str );
            // Recebemos um inteiro válido, resta saber se está dentro da faixa.
            if ( token_int < std::numeric_limits< required_int_type >::min() or
                token_int > std::numeric_limits< required_int_type >::max() )
            {
                // Fora da faixa, reportar erro.
                m_result = ResultType( ResultType::INTEGER_OUT_OF_RANGE, 
                                std::distance( m_expr.begin(), begin_token ) );
            }
            else
            {
                // Coloca o novo token na nossa lista de tokens.
                m_tk_list.emplace_back( Token( token_str, Token::token_t::OPERAND ) );
            }
        }
        else
        {
            skip_ws();
            

            // if( *m_it_curr_symb != m_expr.front() and (std::string("0123456789").find( *m_it_curr_symb ) == std::string::npos) )
            // {

            //     if( *m_it_curr_symb == '(' )
            //     {
            //         m_result =  ResultType( ResultType::ILL_FORMED_INTEGER, 
            //         std::distance( m_expr.begin(), m_it_curr_symb ) ) ;
            //         return false;
            //     }
            // }

            if( m_it_curr_symb == m_expr.begin() and (std::string("*/^%+-").find( *m_it_curr_symb ) != std::string::npos) )
            {
                m_result =  ResultType( ResultType::ILL_FORMED_INTEGER, 
                    std::distance( m_expr.begin(), m_it_curr_symb ) ) ;
                    return false;
            }
            // Create the corresponding error.
            
            // else if( (std::string("*/^%+").find( *m_it_curr_symb ) != std::string::npos) and (std::string("*/^%+").find( *(m_it_curr_symb-1) ) != std::string::npos) or (std::string("*/^%+").find( *(m_it_curr_symb+1) ) != std::string::npos) )
            // {
            //     m_result =  ResultType( ResultType::ILL_FORMED_INTEGER, 
            //         std::distance( m_expr.begin(), m_it_curr_symb ) ) ;
            // }
        }
    } 
     
    return m_result.type == ResultType::OK;
}

/// Validates (i.e. returns true or false) and consumes an **integer** from the input expression string.
/*! This method parses a valid integer from the input and, at the same time, add the integer to the token list.
 *
 * Production rule is:
 * ```
 * <integer> := 0 | ["-"],<natural_number>;
 * ```
 * A integer might be a zero or a natural number, which, in turn, might begin with an unary minus.
 *
 * @return true if an integer has been successfuly parsed from the input; false otherwise.
 */
bool Parser::integer()
{
    // Se aceitarmos um zero, então o inteiro acabou aqui.
    if ( accept( terminal_symbol_t::TS_ZERO ) )
        return true; // OK
    
    accept( terminal_symbol_t::TS_MINUS );
    
    return natural_number();
}

/// Validates (i.e. returns true or false) and consumes a **natural number** from the input string.
/*! This method parses a valid natural number from the input.
 *
 * Production rule is:
 * ```
 * <natural_number> := <digit_excl_zero>,{<digit>};
 * ```
 *
 * @return true if a natural number has been successfuly parsed from the input; false otherwise.
 */
bool Parser::natural_number()
{
    // Tem que vir um número que não seja zero! (de acordo com a definição).
    if ( not digit_excl_zero() )
        return false; // FAILED HERE.

    // Cosumir os demais dígitos, se existirem...
    while( digit() ) /* empty */ ;

    return true; // OK
}

/// Validates (i.e. returns true or false) and consumes a **non-zero digit** from the input expression string.
/*! This method parses a single valid non-zero digit from the input.
 *
 * Production rule is:
 * ```
 * <digit_excl_zero> := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
 * ```
 *
 * @return true if a non-zero digit has been successfuly parsed from the input; false otherwise.
 */
bool Parser::digit_excl_zero()
{
    return accept( terminal_symbol_t::TS_NON_ZERO_DIGIT );
}

/// Validates (i.e. returns true or false) and consumes a **digit** from the input expression string.
/*! This method parses a single valid digit from the input.
 *
 * Production rule is:
 * ```
 * <digit> := "0"| <digit_excl_zero>;
 * ```
 *
 * @return true if a digit has been successfuly parsed from the input; false otherwise.
 */
bool Parser::digit()
{
    return ( accept( terminal_symbol_t::TS_ZERO ) or digit_excl_zero() ) ? true : false;

/*
    if ( not accept( terminal_symbol_t::TS_ZERO ) )
    {
        return digit_excl_zero();
    }
    return true;
*/
}

/*!
 * This is the parser's  **entry point** method that should be called in the client code.
 * This method tries to (recursivelly) validate an expression.
 * During this process, we also store the tokens into a container.
 *
 m e_ The string with the expression to parse.
 * \return The parsing result.
 *
 * @see ResultType
 */

Parser::ResultType Parser::parse( std::string e_ )
{
    m_expr = e_; //  Stores the input expression in the private class member.
    m_it_curr_symb = m_expr.begin(); // Defines the first char to be processed (consumed).
    m_result = ResultType( ResultType::OK ); // Ok, by default,

    // We alway clean up the token from (possible) previous processing.
    m_tk_list.clear();

    // Let us ignore any leading white spaces.
    skip_ws();
    
    if ( m_it_curr_symb+1 == m_expr.end() ) // Premature end?
    {
        // Input has finished before we even started to parse...
        
            m_result =  ResultType( ResultType::UNEXPECTED_END_OF_EXPRESSION,
                std::distance( m_expr.begin(), m_it_curr_symb+2 ) );
    }
    if ( end_input() ) // Premature end?
    {
        // Input has finished before we even started to parse...
        
            m_result =  ResultType( ResultType::UNEXPECTED_END_OF_EXPRESSION,
                std::distance( m_expr.begin(), m_it_curr_symb+1 ) );
    }
    else
    {
        // Trying to validate an expression.
        if ( expression() )
        {
            // At this point there should not be any non-whitespace character in the input expression.
            skip_ws(); // Anyway, let us clear any remaining 'whitespaces'.

            if( closing_last_Count < closing_first_Count )
            {
                m_result = ResultType( ResultType::MISSING_CLOSING_LAST, std::distance( m_expr.begin(), m_it_curr_symb ) );
            }

            if ( not end_input() /*and ( *m_it_curr_symb != '(' and *m_it_curr_symb != ')' )*/ ) // Still got a symbol?
            {
                m_result =  ResultType( ResultType::EXTRANEOUS_SYMBOL,
                        std::distance( m_expr.begin(), m_it_curr_symb ) );
            }
        }
    }
    
    return m_result;
}

/*!
 * Return the list of tokens, which is the by-product created during the syntax analysis.
 * This method should be called in the cliente code **after** tha parser has
 *  returned successfuly.
 */
std::vector< Token >
Parser::get_tokens( void ) const
{
    return m_tk_list;
}

//==========================[ End of parse.cpp ]==========================//
