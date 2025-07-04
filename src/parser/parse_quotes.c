/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/02 16:01:39 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/02 19:26:27 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	concat_last_arg(t_mshell *shell, t_command *cmd, t_parser *p, char *content)
{
	char	*new_arg;

	new_arg = ft_strjoin_s(cmd->args[p->arg_index], content, shell, MEM_TEMP);
	if (!new_arg)
		return (0);
	cmd->args[p->arg_index] = new_arg;
	return (1);
}

int	add_new_arg(t_mshell *shell, t_command *cmd, t_parser *p, char *content)
{
	if (!add_arg_to_cmd(shell, cmd, content))
		return (0);
	p->arg_index = count_args(cmd->args) - 1;
	return (1);
}

int	add_or_concat_arg(t_mshell *shell, t_parser *p)
{
	t_command	*cmd;
	t_token		*tok;
	char		*content;
	int			current_quote_id;

	cmd = p->current_cmd;
	tok = p->current_token;
	if (!cmd || !tok)
		return (0);
	content = tok->content;
	current_quote_id = tok->quote_id;
	if (current_quote_id != -1 && current_quote_id == p->last_quote_id)
		return (concat_last_arg(shell, cmd, p, content));
	else
	{
		p->last_quote_id = current_quote_id;
		return (add_new_arg(shell, cmd, p, content));
	}
}
