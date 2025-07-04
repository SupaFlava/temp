/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:42:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/02 16:58:09 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
// includes
# include "libft.h"
# include "typedefs.h"
# include "utils.h"
# include "builtins.h"

// function prototypes
// lexer.c
t_lexstate	handle_char(t_mshell *shell, t_lexer *l, char c);
int			process_line_loop(t_mshell *shell, t_lexer *l);
void		init_lexer(t_mshell *shell, t_lexer *l);
t_token		*lexer(t_mshell *shell);

// state_handling.c
t_lexstate	default_state(t_mshell *shell, t_lexer *l, char c);
t_lexstate	s_quote_state(t_mshell *shell, t_lexer *l, char c);
t_lexstate	d_quote_state(t_mshell *shell, t_lexer *l, char c);
t_lexstate	env_state(t_mshell *shell, t_lexer *l, char c);
t_lexstate	redir_state(t_mshell *shell, t_lexer *l, char c);

// lexer_utils.c
t_lexstate	append_char_to_buffer(t_mshell *shell, t_lexer *l, char c);
t_lexstate	flush_set_state(t_mshell *sh, t_lexer *l, t_lexstate new_state);
t_lexstate	flush_set_buf(t_mshell *sh, t_lexer *l, const char *s, t_toktype t);
t_lexstate	set_buf_to_char(t_mshell *shell, t_lexer *l, char c);
t_lexstate	check_quote_state(t_lexstate state);

// token_utils.c
t_lexstate	add_token(t_mshell *shell, t_lexer *l, t_toktype type);
void		print_tokens(t_token *tokens);
void		free_tokens(t_token *tokens);
const char	*token_type_to_string(t_toktype type);
t_toktype	find_token_type(const char *buffer, t_lexstate state);

// redir_state_utils.c
t_lexstate	handle_redir_in(t_mshell *shell, t_lexer *l);
t_lexstate	handle_redir_out(t_mshell *shell, t_lexer *l);

// env_state_utils.c
t_lexstate	handle_exit_status(t_mshell *shell, t_lexer *l);
t_lexstate	handle_invalid_env(t_mshell *shell, t_lexer *l, char c);
t_lexstate	handle_empty_buffer_env(t_mshell *shell, t_lexer *l, char c);

// assign.c
t_lexstate	assign_state(t_mshell *shell, t_lexer *l, char c);
t_lexstate	handle_assign_state(t_mshell *shell, t_lexer *l, char c);

// validate.c
int			validate_tokens(t_lexer *l);
int			finalize_tokens(t_mshell *shell, t_lexer *l);

// quotes_logic.c
void		start_new_quote_group(t_lexer *l);
void		end_quote_group(t_lexer *l);
int			get_quote_id(t_lexer *l);

//TEMP!!!!!
void		print_command(t_command *cmd);

#endif /*LEXER_H*/