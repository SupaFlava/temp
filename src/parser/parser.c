/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:20:07 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/13 17:44:25 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_parser_state	parse_env(t_mshell *shell, t_parser *p)
{
	t_token	*tok;
	t_env	*expanded;

	tok = p->current_token;
	if (!p->current_cmd)
	{
		p->current_cmd = init_command(shell, p);
		if (!p->current_cmd)
			return (PARSE_ERROR);
	}
	if (tok->type == TOK_ENV_VAR)
	{
		expanded = get_env(shell->env_list, tok->content);
		if (!expanded || !expanded->value)
			expanded->value = ft_strdup_s(shell, "", MEM_LONG);
		add_arg_to_cmd(shell, p->current_cmd, expanded->value);
	}
	else if (tok->type == TOK_EXIT_STATUS)
	{
		p->exit_value = ft_itoa_s(shell, shell->exit_status, MEM_LONG);
		add_arg_to_cmd(shell, p->current_cmd, p->exit_value);
	}
	else
		return (PARSE_ERROR);
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
	new_cmd = init_command(shell, p);
	if (!new_cmd)
		return (PARSE_ERROR);
	p->current_cmd = new_cmd;
	return (PARSE_DEFAULT);
}

t_parser_state	parse_word(t_mshell *shell, t_parser *p)
{
	if (!p->current_cmd)
	{
		p->current_cmd = init_command(shell, p);
		if (!p->current_cmd)
			return (PARSE_ERROR);
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
	init_parser(shell, p);
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
