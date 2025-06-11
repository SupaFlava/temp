/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:42:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 02:04:18 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
// includes
# include "libft.h"
# include "typedefs.h"
# include "utils.h"

// lexer functions
t_lexer_state 	handle_char(t_mshell *shell, t_lexer *l, char c);
t_lexer_state	finalize_tokens(t_mshell *shell, t_lexer *l);
void			init_lexer(t_mshell *shell, t_lexer *l);
t_token			*lexer(t_mshell *shell);

// lexer state functions
t_lexer_state	default_state(t_mshell *shell, t_lexer *l, char c);
t_lexer_state	s_quote_state(t_mshell *shell, t_lexer *l, char c);
t_lexer_state	d_quote_state(t_mshell *shell, t_lexer *l, char c);
t_lexer_state	env_state(t_mshell *shell, t_lexer *l, char c);
t_lexer_state	redir_state(t_mshell *shell, t_lexer *l, char c);

// lexer_utils.c
int				check_quote_state(t_lexer_state *state);
int				append_char_to_buffer(t_mshell *shell, t_lexer *l, char c);
int				flush_set_state(t_mshell *shell, t_lexer *l, t_lexer_state new_state);
t_lexer_state	flush_set_buf(t_mshell *shell, t_lexer *l, const char *s, t_toktype type);
t_lexer_state	set_buf_to_char(t_mshell *shell, t_lexer *l, char c);

// token_utils.c
int				add_token(t_mshell *shell, t_lexer *l, t_toktype type);
void			print_tokens(t_token *tokens);
void			free_tokens(t_token *tokens);
const char		*token_type_to_string(t_toktype type);
t_toktype		find_token_type(const char *buffer, t_lexer_state state);
const char		*token_type_to_string(t_toktype type);


// redir_state_utils.c
t_lexer_state	handle_redir_in(t_mshell *shell, t_lexer *l);
t_lexer_state	handle_redir_out(t_mshell *shell, t_lexer *l);

// env_state_utils.c
t_lexer_state	handle_exit_status(t_mshell *shell, t_lexer *l);
t_lexer_state	handle_invalid_char(t_mshell *shell, t_lexer *l, char c);

// buffer_utils.c
#endif /*LEXER_H*/