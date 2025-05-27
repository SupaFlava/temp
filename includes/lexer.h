/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:42:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/20 17:06:57 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
// includes
# include "libft.h"
# include "typedefs.h"
# include "utils.h"

// function prototypes
// state_handling.c
int			default_state(t_mshell *shell, t_state *state, char c, char **buffer);
int			s_quote_state(t_mshell *shell, t_state *state, char c, char **buffer);
int			d_quote_state(t_mshell *shell, t_state *state, char c, char **buffer);
int			env_state(t_mshell *shell, t_state *state, char c, char **buffer);
int			redir_state(t_mshell *shell, t_state *state, char c, char **buffer);

// lexer.c
int			handle_char(t_mshell *shell, t_state *state, char c, char **buffer);
int			process_line_loop(t_mshell *shell, t_state *state, char **buffer);
void		init_lexer(t_mshell *shell, t_state *state, char **buffer);
int			finalize_tokens(t_mshell *shell, t_state *state, char **buffer);
t_token		*lexer(t_mshell *shell);

// lexer_utils.c
int			append_char_to_buffer(t_mshell *shell, char **buffer, char c);
int			flush_set_state(t_mshell *shell, char **buf, t_state *state, t_state n_state);
int			flush_set_buf(t_mshell *shell, char **buf, const char *s, t_toktype type);
int			set_buf_to_char(t_mshell *shell, char **buf, char c);
int			check_quote_state(t_state *state);

// token_utils.c
int			add_token(t_mshell *shell, char **buffer, t_toktype type);
void		print_tokens(t_token *tokens);
void		free_tokens(t_token *tokens);
const char	*token_type_to_string(t_toktype type);
t_toktype	find_token_type(const char *buffer, t_state state);

// redir_state_utils.c
int			handle_redir_in(t_mshell *shell, char **buf, t_state *state);
int			handle_redir_out(t_mshell *shell, char **buf, t_state *state);

// env_state_utils.c
int	handle_exit_status(t_mshell *shell, t_state *state, char **buffer);
int	handle_invalid_char(t_mshell *shell, t_state *state, char c, char **buffer);
int	handle_valid_char(t_mshell *shell, char c, char **buffer);

// buffer_utils.c
#endif /*LEXER_H*/