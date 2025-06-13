/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 22:42:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/13 17:33:27 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_state	parse_redir(t_mshell *shell, t_parser *p)
{
	t_token	*current;

	if (!p->current_cmd)
		return (PARSE_ERROR);
	current = p->current_token;
	if (!current || (current->type != TOK_WORD && current->type != TOK_QUOTED))
		return (PARSE_ERROR);
	p->current_cmd->infile = ft_strdup_s(shell, current->content, MEM_TEMP);
	if (!p->current_cmd->infile)
		return (PARSE_ERROR);
	return (PARSE_DEFAULT);
}

t_parser_state	parse_append(t_mshell *shell, t_parser *p)
{
	t_token	*current;

	if (!p->current_cmd)
		return (PARSE_ERROR);
	current = p->current_token;
	if (!current || (current->type != TOK_WORD && current->type != TOK_QUOTED))
		return (PARSE_ERROR);
	p->current_cmd->outfile = ft_strdup_s(shell, current->content, MEM_TEMP);
	p->current_cmd->append = 1;
	return (PARSE_DEFAULT);
}

t_parser_state	parse_heredoc(t_mshell *shell, t_parser *p)
{
	t_token	*current;

	if (!p->current_cmd)
	{
		p->current_cmd = init_command(shell, p);
		if (!p->current_cmd)
			return (PARSE_ERROR);
	}
	current = p->current_token;
	if (!current || (current->type != TOK_WORD && current->type != TOK_QUOTED))
		return (PARSE_ERROR);
	p->current_cmd->delimiter = ft_strdup_s(shell, current->content, MEM_TEMP);
	return (PARSE_DEFAULT);
}
