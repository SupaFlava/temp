/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:42:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/08 16:34:24 by jbaetsen      ########   odam.nl         */
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
void	handle_default_state(t_state *state, char c, char **buffer, t_token **tokens);
void	handle_single_quote(t_state *state, char c, char **buffer, t_token **tokens);
void	handle_double_quote(t_state *state, char c, char **buffer, t_token **tokens);
void	handle_env_state(t_state *state, char c, char **buffer, t_token **tokens);
void	handle_redir_state(t_state *state, char c, char **buffer, t_token **tokens);

// lexer.c
void			handle_char(t_state *state, char c, char **buffer, t_token **tokens);
void			append_char_to_buffer(char **buffer, char c);
t_token_type	find_token_type(const char *buffer, t_state state);
t_token 		*lexer(const char *input);
void			add_token(t_token **tokens, char *buffer, t_token_type type);


#endif /*LEXER_H*/