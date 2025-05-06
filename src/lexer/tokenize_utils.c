/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:59:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/06 16:36:19 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int is_escape(char c)
{
    return (c == '\\');
}

int is_quote(char c)
{
    return (c == '\'' || c == '\"');
}

int is_operator(char c)
{
    return (c == '|' || c == '>' || c == '<' || c == '&');
}

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
        || c == '\v' || c == '\f' || c == '\r');
}

int handle_state(int *state, char c, char **token)
{
    if (is_quote(c))
    else if (is_escape(c))
    else if (c == '$')
    else if (is_operator(c))
}


// int handle_state(int *state, char c, char **token)
// {
//     if (*state = STATE_ESCAPE)
//     {
//         *token = add_char_to_token(*token, c)
//         *state = STATE_DEFAULT;
//         return (1);
//     }
//     if (c == '\'' && *state == STATE_DEFAULT)
//     {
//         *state = STATE_IN_SINGLE_QUOTE;
//         return (1);
//     }
//     if (c == '\'' && *state == STATE_IN_SINGLE_QUOTE)
//     {
//         *state = STATE_DEFAULT;
//         return (1);
//     }
//     if (c == '\"' && state == STATE_DEFAULT)
//     {
//         *state = STATE_IN_DOUBLE_QUOTE
//         return (1);
//     }
//     if (c == '\"' && state == STATE_IN_DOUBLE_QUOTE)
//     {
//         *state = STATE_DEFAULT;
//         return (1);
//     }
//     return (0);   
// }