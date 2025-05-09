/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:42:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/09 19:43:11 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
// includes
# include "libft.h"
# include "typedefs.h"
# include "utils.h"

// function prototypes
// tokenize_utils.c
void	default_state(t_state *state, char c, char **buffer, t_token **tokens);
void	s_quote_state(t_state *state, char c, char **buffer, t_token **tokens);
void	d_quote_state(t_state *state, char c, char **buffer, t_token **tokens);
void	env_state(t_state *state, char c, char **buffer, t_token **tokens);
void	redir_state(t_state *state, char c, char **buffer, t_token **tokens);

// lexer.c
void	handle_char(t_state *state, char c, char **buffer, t_token **tokens);
void	append_char_to_buffer(char **buffer, char c);
t_token	*lexer(const char *input);
void	add_token(t_token **tokens, char *buffer, t_token_type type);

#endif /*LEXER_H*/