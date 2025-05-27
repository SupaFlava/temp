/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 15:50:26 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/27 23:44:53 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// includes
# include "typedefs.h"
# include "utils.h"

// function prototypes
// parser.c
t_command	*parse_tokens_to_cmds(t_mshell *shell);
int			append_to_args(t_mshell *shell, t_command *command, char *content);


// parser_utils.c
char		*read_input(void);
t_command	*create_command(t_mshell *shell);
int			parse_nonredir_token(t_mshell *shell, t_token *token, t_command *command);
int			parse_redir_token(t_mshell *shell, t_token *token, t_command *command);



#endif