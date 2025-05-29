/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:20:07 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/29 21:25:38 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_state	handle_parse_word_state(t_mshell *shell, t_parser *p)
{
	t_toktype tok = p->current_token->type;

	if (tok == TOK_WORD || tok == TOK_QUOTED
		|| tok == TOK_ENV_VAR || tok == TOK_EXIT_STATUS)
		return parse_word(shell, p);
	else if (tok == TOK_REDIR_IN)
		return PARSE_REDIR;
	else if (tok == TOK_REDIR_OUT)
		return PARSE_APPEND;
	else if (tok == TOK_APPEND)
		return PARSE_APPEND;
	else if (tok == TOK_HEREDOC)
		return PARSE_HEREDOC;
	else if (tok == TOK_PIPE)
		return PARSE_PIPE;
	else
		return PARSE_ERROR;
}

t_parser_state	parse_redir(t_mshell *shell, t_parser *p)
{
	t_token	*next;

	next = p->current_token->next;
	if (!next || (next->type != TOK_WORD && next->type != TOK_QUOTED))
		return (PARSE_ERROR);
	p->current_cmd->infile = ft_strdup_s(shell, next->content, MEM_TEMP);
	p->current_token = next;
	if (!p->current_cmd->infile)
		return (PARSE_ERROR);
	return (PARSE_WORD);

}

t_parser_state	parse_append(t_mshell *shell, t_parser *p)
{
	t_token	*next;

	next = p->current_token->next;
	if (!next || (next->type != TOK_WORD && next->type != TOK_QUOTED))
		return (PARSE_ERROR);
	p->current_cmd->outfile = ft_strdup_s(shell, next->content, MEM_TEMP);
	p->current_token = next;
	p->current_cmd->append = 1;
	return (PARSE_WORD);
}

t_parser_state	parse_heredoc(t_mshell *shell, t_parser *p)
{
	t_token	*next;

	next = p->current_token->next;
	if (!next || (next->type != TOK_WORD && next->type != TOK_QUOTED))
		return (PARSE_ERROR);
	p->current_cmd->infile = ft_strdup_s(shell, next->content, MEM_TEMP);
	p->current_token = next;
	return (PARSE_WORD);

}


t_parser_state	parse_pipe(t_mshell *shell, t_parser *p)
{
	t_command	*new_cmd;
	t_command	*last;

	if (!p->current_cmd)
		return (PARSE_ERROR);
	if (!p->cmd_list)
		p->cmd_list = p->current_cmd;
	else
	{
		last = p->cmd_list;
		while (last->next)
			last = last->next;
		last->next = p->current_cmd;
	}
	new_cmd = ft_malloc_s(shell, sizeof(t_command), MEM_TEMP);
	if (!new_cmd)
		return (PARSE_ERROR);
	ft_bzero(new_cmd, sizeof(t_command));
	p->current_cmd = new_cmd;
	return (PARSE_START);
}

t_parser_state	parse_word(t_mshell *shell, t_parser *p)
{
	if (!p->current_cmd)
	{
		p->current_cmd = ft_malloc_s(shell, sizeof(t_command), MEM_TEMP);
		if (!p->current_cmd)
			return (PARSE_ERROR);
		ft_bzero(p->current_cmd, sizeof(t_command));
		if (!p->cmd_list)
			p->cmd_list = p->current_cmd;
	}
	add_arg_to_cmd(shell, p->current_cmd, p->current_token->content);
	return (PARSE_WORD);
}

t_parser_state	parse_start(t_mshell *shell, t_parser *p)
{
	t_toktype	tok;

	tok = p->current_token->type;

	if (tok == TOK_WORD || tok == TOK_QUOTED
		|| tok == TOK_ENV_VAR || tok == TOK_EXIT_STATUS)
		return (parse_word(shell, p));
	else if (tok == TOK_REDIR_IN)
		return (PARSE_REDIR);
	else if (tok == TOK_REDIR_OUT)
		return (PARSE_APPEND);
	else if (tok == TOK_APPEND)
		return (PARSE_APPEND);
	else if (tok == TOK_HEREDOC)
		return (PARSE_HEREDOC);
	else if (tok == TOK_PIPE)
		return (PARSE_PIPE);
	else
		return (PARSE_ERROR);
}

t_command	*parse_tokens_to_cmds(t_mshell *shell)
{
	t_parser	*p;

	p = ft_malloc_s(shell, sizeof(t_parser), MEM_TEMP);
	if (!p)
		return (NULL);
	init_parser(p, shell);

	while(p->current_token)
	{
		ft_printf("Parsing token: %s (type %d, state %d)\n",
			p->current_token->content,
			p->current_token->type,
			p->state);

		if (p->state == PARSE_START)
			p->state = parse_start(shell, p);
		else if (p->state == PARSE_WORD)
			p->state = handle_parse_word_state(shell, p);
		else if (p->state == PARSE_REDIR)
			p->state = parse_redir(shell, p);
		else if (p->state == PARSE_HEREDOC)
			p->state = parse_heredoc(shell, p);
		else if (p->state == PARSE_APPEND)
			p->state = parse_append(shell, p);
		else if (p->state == PARSE_PIPE)
			p->state = parse_pipe(shell, p);
		else
			return (NULL);
		if (p->state == PARSE_ERROR)
			return (NULL);
		p->current_token = p->current_token->next;
	}
	return (p->cmd_list);
}
