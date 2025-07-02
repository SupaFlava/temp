/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redir_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/19 21:26:00 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/02 12:43:02 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_redir_state(t_parser *p)
{
	if (p->state == PARSE_REDIR
		|| p->state == PARSE_APPEND
		|| p->state == PARSE_HEREDOC)
	{
		print_err("minishell", NULL,
			"syntax error near unexpected token `newline'");
		return (1);
	}
	return (0);
}

int	ensure_current_cmd(t_mshell *shell, t_parser *p)
{
	if (!p->current_cmd)
		p->current_cmd = init_command(shell, p);
	return (p->current_cmd != NULL);
}
