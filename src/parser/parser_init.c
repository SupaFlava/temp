/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/13 17:40:49 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/04 22:08:40 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*init_command(t_mshell *shell, t_parser *p)
{
	t_command	*cmd;

	cmd = ft_malloc_s(shell, sizeof(t_command), MEM_TEMP);
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_command));
	cmd->next = NULL;
	if (!p->cmd_list)
		p->cmd_list = cmd;
	return (cmd);
}

void	init_parser(t_mshell *shell, t_parser *p)
{
	p->current_token = shell->tokens;
	p->cmd_list = NULL;
	p->current_cmd = NULL;
	p->state = PARSE_DEFAULT;
	p->env = shell->env_list;
	p->exit_value = ft_itoa_s(shell, shell->exit_status, MEM_LONG);
	p->last_token_type = TOK_WORD;
	p->arg_index = -1;
}
