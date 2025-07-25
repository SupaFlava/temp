/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:20:07 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/07/05 23:14:04 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_parser_state	parse_env(t_mshell *sh, t_parser *p)
{
	t_token	*tok;
	t_env	*expanded;

	tok = p->current_token;
	if (!ensure_current_cmd(sh, p))
		return (PARSE_ERROR);
	if (tok->type == TOK_ENV_VAR)
	{
		expanded = expand_env(sh, tok->content);
		p->current_token->content = ft_strdup_s(sh, expanded->value, MEM_TEMP);
	}
	else
		return (PARSE_ERROR);
	if (!add_or_concat_arg(sh, p))
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
	if (!ensure_current_cmd(shell, p))
		return (PARSE_ERROR);
	if (!add_or_concat_arg(shell, p))
		return (PARSE_ERROR);
	return (PARSE_DEFAULT);
}

t_parser_state	parse_token(t_mshell *shell, t_parser *p)
{
	t_toktype	tok;

	tok = p->current_token->type;
	if (tok == TOK_WORD || tok == TOK_QUOTED || tok == TOK_ASSIGN)
		return (parse_word(shell, p));
	else if (tok == TOK_ENV_VAR)
		return (parse_env(shell, p));
	else if (tok == TOK_PIPE)
		return (parse_pipe(shell, p));
	else if (tok == TOK_REDIR_IN)
		return (PARSE_REDIR);
	else if (tok == TOK_REDIR_OUT)
		return (PARSE_APPEND);
	else if (tok == TOK_APPEND)
	{
		p->current_cmd->append = 1;
		return (PARSE_APPEND);
	}
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
			p->state = parse_infile(shell, p);
		else if (p->state == PARSE_APPEND)
			p->state = parse_outfile(shell, p);
		else if (p->state == PARSE_HEREDOC)
			p->state = parse_heredoc(shell, p);
		else
			p->state = parse_token(shell, p);
		if (p->state == PARSE_ERROR)
			return (NULL);
		p->last_token_type = p->current_token->type;
		p->current_token = p->current_token->next;
	}
	if (check_redir_state(p))
		return (NULL);
	finalize_command(p);
	return (p->cmd_list);
}
