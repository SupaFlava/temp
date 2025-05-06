/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:47:24 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/06 15:51:27 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void    add_char_to_token(char **token, char c)
{

}

void    flush_token(char **token, t_token **tokens)
{
    
}

int handle_state(int *state, char c, char **token)
{
    if (*state = STATE_ESCAPE)
    {
        *token = add_char_to_token(*token, c)
        *state = STATE_DEFAULT;
        return (1);
    }
    if (c == '\'' && *state == STATE_DEFAULT)
    {
        *state = STATE_IN_SINGLE_QUOTE;
        return (1);
    }
    if (c == '\'' && *state == STATE_IN_SINGLE_QUOTE)
    {
        *state = STATE_DEFAULT;
        return (1);
    }
    if (c == '\"' && state == STATE_DEFAULT)
    {
        *state = STATE_IN_DOUBLE_QUOTE
        return (1);
    }
    if (c == '\"' && state == STATE_IN_DOUBLE_QUOTE)
    {
        *state = STATE_DEFAULT;
        return (1);
    }
    return (0);   
}

t_token  *lex_input(const char *input)
{
    int i;
    int state;
    char *token;
    t_token *tokens;
    char    c

    i = 0;
    state = STATE_DEFAULT;
    token = NULL;
    tokens == NULL;
    
    while (input[i]) // read input 1 character at a time
    {
        c = input[i];
        if (handle_state(&state, c, &token)) // set state based on currect character. check for words, strings, symbols/operators
        {
            i++;
            continue;
        }
        if (is_space(c) && state == STATE_DEFAULT)
            flush_token(&token, tokens);
        else if (is operator_start(c) && state == STATE_DEFAULT)
            flush_token(&token, &tokens);



            
        i++;
    }
}
