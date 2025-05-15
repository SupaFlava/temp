/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:42:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/15 16:28:00 by jbaetsen      ########   odam.nl         */
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
int		default_state(t_mshell *shell, t_state *state, char c, char **buffer);
int		s_quote_state(t_mshell *shell, t_state *state, char c, char **buffer);
int		d_quote_state(t_mshell *shell, t_state *state, char c, char **buffer);
int		env_state(t_mshell *shell, t_state *state, char c, char **buffer);
int		redir_state(t_mshell *shell, t_state *state, char c, char **buffer);

// lexer.c
int		handle_char(t_mshell *shell, t_state *state, char c, char **buffer);
int		append_char_to_buffer(t_mshell *shell, char **buffer, char c);
t_token	*lexer(t_mshell *shell);
int		add_token(t_mshell *shell, char *buffer, t_token_type type);

#endif /*LEXER_H*/