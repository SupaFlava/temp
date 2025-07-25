/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 15:50:26 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/08 11:29:31 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// includes
# include "typedefs.h"
# include "parsequotes.h"
# include "utils.h"

// function prototypes
// parser.c
t_command		*parser(t_mshell *shell);
t_parser_state	parse_start(t_mshell *shell, t_parser *p);
t_parser_state	parse_word(t_mshell *shell, t_parser *p);
t_parser_state	parse_pipe(t_mshell *shell, t_parser *p);

// parse_redirs.c
void			add_infile(t_mshell *shell, t_command *cmd, char *file);
void			add_outfile(t_mshell *sh, t_command *cmd, char *file, bool app);
t_parser_state	parse_infile(t_mshell *shell, t_parser *p);
t_parser_state	parse_outfile(t_mshell *shell, t_parser *p);
t_parser_state	parse_heredoc(t_mshell *shell, t_parser *p);

// parser_redirs_utils.c
int				check_redir_state(t_parser *p);
int				ensure_current_cmd(t_mshell *shell, t_parser *p);

// parser_utils.c
t_env			*expand_env(t_mshell *shell, char *key);
void			finalize_command(t_parser *p);
char			*read_input(void);
void			process_input(t_mshell *shell);
int				add_arg_to_cmd(t_mshell *shell, t_command *command, char *arg);

// init_parser.c
void			init_parser(t_mshell *shell, t_parser *p);
t_command		*init_command(t_mshell *shell, t_parser *p);

#endif