/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:20:07 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/04 22:25:07 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_parser_state	parse_env(t_mshell *shell, t_parser *p)
{
	t_token	*tok;
	char	*expanded;

	tok = p->current_token;
	if (!p->current_cmd)
	{
		p->current_cmd = ft_malloc_s(shell, sizeof(t_command), MEM_TEMP);
		if (!p->current_cmd)
			return (PARSE_ERROR);
		ft_bzero(p->current_cmd, sizeof(t_command));
		p->current_cmd->next = NULL;
		if (!p->cmd_list)
			p->cmd_list = p->current_cmd;
	}

	if (tok->type == TOK_ENV_VAR)
		expanded = get_env(shell->env_list, tok->content);
	// else if (tok->type == TOK_EXIT_STATUS)
		//WIP: exit status logic here
	else
		return (PARSE_ERROR);
	if (!expanded)
		expanded = ft_strdup_s(shell, "", MEM_LONG);
	add_arg_to_cmd(shell, p->current_cmd, expanded);
	return (PARSE_DEFAULT);
}

t_parser_state	parse_pipe(t_mshell *shell, t_parser *p)
{
	t_command	*new_cmd;
	t_command	*last;

	last = NULL;
	if (!p->current_cmd)
		return (PARSE_ERROR);
	if (!p->cmd_list)
		p->cmd_list = p->current_cmd;
	else
	{
		last = p->cmd_list;
		while (last->next)
			last = last->next;
		if (last != p->current_cmd)
			last->next = p->current_cmd;
	}
	new_cmd = ft_malloc_s(shell, sizeof(t_command), MEM_TEMP);
	if (!new_cmd)
		return (PARSE_ERROR);
	ft_bzero(new_cmd, sizeof(t_command));
	new_cmd->next = NULL;
	p->current_cmd = new_cmd;
	return (PARSE_DEFAULT);
}

t_parser_state	parse_redir(t_mshell *shell, t_parser *p)
{
	t_token	*current;

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

	current = p->current_token;
	if (!current || (current->type != TOK_WORD && current->type != TOK_QUOTED))
		return (PARSE_ERROR);
	p->current_cmd->infile = ft_strdup_s(shell, current->content, MEM_TEMP);
	return (PARSE_DEFAULT);

}

t_parser_state	parse_word(t_mshell *shell, t_parser *p)
{
	if (!p->current_cmd)
	{
		p->current_cmd = ft_malloc_s(shell, sizeof(t_command), MEM_TEMP);
		if (!p->current_cmd)
			return (PARSE_ERROR);
		ft_bzero(p->current_cmd, sizeof(t_command));
		p->current_cmd->next = NULL;
		if (!p->cmd_list)
			p->cmd_list = p->current_cmd;
	}
	add_arg_to_cmd(shell, p->current_cmd, p->current_token->content);
	return (PARSE_DEFAULT);
}

t_parser_state	parse_token(t_mshell *shell, t_parser *p)
{
	t_toktype	tok;

	tok = p->current_token->type;

	if (tok == TOK_WORD || tok == TOK_QUOTED)
		return (parse_word(shell, p));
	else if (tok == TOK_ENV_VAR || tok == TOK_EXIT_STATUS)
		return (parse_env(shell, p));
	else if (tok == TOK_PIPE)
		return (parse_pipe(shell, p));
	else if (tok == TOK_REDIR_IN)
		return (PARSE_REDIR);
	else if (tok == TOK_REDIR_OUT)
		return (PARSE_APPEND);
	else if (tok == TOK_APPEND)
		return (PARSE_APPEND);
	else if (tok == TOK_HEREDOC)
		return (PARSE_HEREDOC);
	else
	{
		ft_printf("parser error\n");
		return (PARSE_ERROR);
	}
}

t_command	*parser(t_mshell *shell)
{
	t_parser	*p;

	p = ft_malloc_s(shell, sizeof(t_parser), MEM_TEMP);
	if (!p)
		return (NULL);
	init_parser(p, shell);
	while (p->current_token)
	{
		if (p->state == PARSE_REDIR)
			p->state = parse_redir(shell, p);
		else if (p->state == PARSE_APPEND)
			p->state = parse_append(shell, p);
		else if (p->state == PARSE_HEREDOC)
			p->state = parse_heredoc(shell, p);
		else
			p->state = parse_token(shell, p);
		if (p->state == PARSE_ERROR)
			return (NULL);
		p->current_token = p->current_token->next;
	}
	finalize_command(p);
	return (p->cmd_list);
}
