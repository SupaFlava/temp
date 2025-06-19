/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redirs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 22:42:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/19 21:33:25 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void	add_infile(t_mshell *shell, t_command *cmd, char *file)
{
	t_redir	*current;
	t_redir	*node;

	current = cmd->infile;
	node = ft_malloc_s(shell, sizeof(t_redir), MEM_TEMP);
	node->file = ft_strdup_s(shell, file, MEM_TEMP);
	if (!node->file)
		return ;
	node->append = false;
	node->next = NULL;
	if (!cmd->infile)
		cmd->infile = node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

void	add_outfile(t_mshell *shell, t_command *cmd, char *file, bool append)
{
	t_redir	*current;
	t_redir	*node;

	current = cmd->outfile;
	node = ft_malloc_s(shell, sizeof(t_redir), MEM_TEMP);
	node->file = ft_strdup_s(shell, file, MEM_TEMP);
	node->append = append;
	node->next = NULL;
	if (!cmd->outfile)
		cmd->outfile = node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = node;
	}
	cmd->append = append;
}

t_parser_state	parse_infile(t_mshell *shell, t_parser *p)
{
	t_token	*current;
	t_env	*expanded;
	char	*file;

	if (!ensure_current_cmd(shell, p))
		return (PARSE_ERROR);
	current = p->current_token;
	if (!p->current_cmd || !current)
		return (PARSE_ERROR);
	if (current->type == TOK_WORD || current->type == TOK_QUOTED)
		file = ft_strdup_s(shell, current->content, MEM_TEMP);
	else if (current->type == TOK_ENV_VAR)
	{
		expanded = expand_env(shell, current->content);
		if (!expanded || !expanded->value)
			return (PARSE_ERROR);
		file = expanded->value;
	}
	else
		return (PARSE_ERROR);
	add_infile(shell, p->current_cmd, file);
	return (PARSE_DEFAULT);
}

t_parser_state	parse_outfile(t_mshell *shell, t_parser *p)
{
	t_token	*current;
	t_env	*expanded;
	char	*file;

	if (!ensure_current_cmd(shell, p))
		return (PARSE_ERROR);
	current = p->current_token;
	if (!p->current_cmd || !current)
		return (PARSE_ERROR);
	if (current->type == TOK_WORD || current->type == TOK_QUOTED)
		file = ft_strdup_s(shell, current->content, MEM_TEMP);
	else if (current->type == TOK_ENV_VAR)
	{
		expanded = expand_env(shell, current->content);
		if (!expanded || !expanded->value)
			return (PARSE_ERROR);
		file = expanded->value;
	}
	else
		return (PARSE_ERROR);
	add_outfile(shell, p->current_cmd, file, p->current_cmd->append);
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
	p->current_cmd->is_heredoc = true;
	return (PARSE_DEFAULT);
}
