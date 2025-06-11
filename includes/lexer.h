/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:42:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 20:45:46 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
// includes
# include "libft.h"
# include "typedefs.h"
# include "utils.h"

// function prototypes
// lexer.c
t_lexer_state	handle_char(t_mshell *shell, t_lexer *l, char c); //done
int				process_line_loop(t_mshell *shell, t_lexer *l); //done
void			init_lexer(t_mshell *shell, t_lexer *l); //done
int				finalize_tokens(t_mshell *shell, t_lexer *l); //done
t_token			*lexer(t_mshell *shell);

// state_handling.c
t_lexer_state	default_state(t_mshell *shell, t_lexer *l, char c); //done
t_lexer_state	s_quote_state(t_mshell *shell, t_lexer *l, char c); // done
t_lexer_state	d_quote_state(t_mshell *shell, t_lexer *l, char c); //done
t_lexer_state	env_state(t_mshell *shell, t_lexer *l, char c); //done
t_lexer_state	redir_state(t_mshell *shell, t_lexer *l, char c); //done


// lexer_utils.c
t_lexer_state	append_char_to_buffer(t_mshell *shell, t_lexer *l, char c); //done
t_lexer_state	flush_set_state(t_mshell *sh, t_lexer *l, t_lexer_state new_state); //done
t_lexer_state	flush_set_buf(t_mshell *sh, t_lexer *l, const char *s, t_toktype type); //done
t_lexer_state	set_buf_to_char(t_mshell *shell, t_lexer *l, char c); //done
t_lexer_state	check_quote_state(t_lexer_state state);

// token_utils.c
t_lexer_state	add_token(t_mshell *shell, t_lexer *l, t_toktype type); //done
void			print_tokens(t_token *tokens); //not needed?
void			free_tokens(t_token *tokens); //not needed?
const char		*token_type_to_string(t_toktype type); //not needed?
t_toktype		find_token_type(const char *buffer, t_lexer_state state); //done

// redir_state_utils.c
t_lexer_state	handle_redir_in(t_mshell *shell, t_lexer *l); //done
t_lexer_state	handle_redir_out(t_mshell *shell, t_lexer *l); //done

// env_state_utils.c
t_lexer_state	handle_exit_status(t_mshell *shell, t_lexer *l); //done
t_lexer_state	handle_invalid_char(t_mshell *shell, t_lexer *l, char c); //done
int	ft_str_is_valid_env(const char *s);


// buffer_utils.c
#endif /*LEXER_H*/