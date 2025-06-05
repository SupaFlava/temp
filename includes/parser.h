/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 15:50:26 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/04 22:44:34 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// includes
# include "typedefs.h"
# include "utils.h"

// function prototypes
// parser.c
t_command		*parser(t_mshell *shell);
t_parser_state	parse_start(t_mshell *shell, t_parser *p);
t_parser_state	parse_word(t_mshell *shell, t_parser *p);
t_parser_state	parse_pipe(t_mshell *shell, t_parser *p);

// parse_redirs.c
t_parser_state	parse_redir(t_mshell *shell, t_parser *p);
t_parser_state	parse_append(t_mshell *shell, t_parser *p);
t_parser_state	parse_heredoc(t_mshell *shell, t_parser *p);

// parser_utils.c
void	finalize_command(t_parser *p);
char	*read_input(void);
void	init_parser(t_parser *p, t_mshell *shell);
void	add_arg_to_cmd(t_mshell *shell, t_command *command, char *arg);



#endif