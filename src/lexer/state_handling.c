/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:59:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/08 12:38:42 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexstate	default_state(t_mshell *shell, t_lexer *l, char c)
{
	if (c == ' ' || c == '\t')
		return (add_token(shell, l, TOK_WORD));
	else if (c == '\'')
		return (LEXER_SQUOTE);
	else if (c == '\"')
	{
		start_new_quote_group(l);
		return (LEXER_DQUOTE);
	}
	else if (c == '|')
		return (flush_set_buf(shell, l, "|", TOK_PIPE));
	else if (c == '<')
		return (handle_redir_in(shell, l));
	else if (c == '>')
		return (handle_redir_out(shell, l));
	else if (c == '=' && l->buffer)
		return (handle_assign_state(shell, l, c));
	else if (c == '$')
		return (LEXER_ENV);
	return (append_char_to_buffer(shell, l, c));
}

t_lexstate	s_quote_state(t_mshell *shell, t_lexer *l, char c)
{
	if (c == '\'')
	{
		if (l->input[l->index + 1] == '\'')
			return (LEXER_DEFAULT);
		l->state = LEXER_DEFAULT;
		return (add_token (shell, l, TOK_QUOTED));
	}
	return (append_char_to_buffer(shell, l, c));
}

t_lexstate	d_quote_state(t_mshell *shell, t_lexer *l, char c)
{
	if (c == '"')
	{
		if (l->input[l->index + 1] == '"')
		{
			l->index++;
			return (LEXER_DQUOTE);
		}
		else if (l->input[l->index + 1] != ' ')
			return (LEXER_DEFAULT);
		if (l->buffer && add_token(shell, l, TOK_QUOTED) == LEXER_ERROR)
			return (LEXER_ERROR);
		end_quote_group(l);
		return (LEXER_DEFAULT);
	}
	else if (c == '$' && l->input[l->index + 1] != ' ')
	{
		if (l->buffer && add_token(shell, l, TOK_QUOTED) == LEXER_ERROR)
			return (LEXER_ERROR);
		return (LEXER_QUOTED_ENV);
	}
	return (append_char_to_buffer(shell, l, c));
}

t_lexstate	env_state(t_mshell *shell, t_lexer *l, char c)
{
	if (c == '?')
		return (handle_exit_status(shell, l));
	if (!ft_isalnum(c) && c != '_')
		return (handle_invalid_env(shell, l, c));
	if (!l->buffer && !ft_isalpha(c) && c != '_')
	{
		if (append_char_to_buffer(shell, l, '$') == LEXER_ERROR)
			return (LEXER_ERROR);
		if (append_char_to_buffer(shell, l, c) == LEXER_ERROR)
			return (LEXER_ERROR);
		return (LEXER_DEFAULT);
	}
	if (l->buffer && !is_valid_env(l->buffer))
	{
		if (add_token(shell, l, TOK_WORD) == LEXER_ERROR)
			return (LEXER_ERROR);
	}
	return (append_char_to_buffer(shell, l, c));
}

t_lexstate	redir_state(t_mshell *shell, t_lexer *l, char c)
{
	t_toktype	t;

	if ((l->state == LEXER_REDIR_IN && c == '<')
		|| (l->state == LEXER_REDIR_OUT && c == '>'))
		return (append_char_to_buffer(shell, l, c));
	if (ft_strcmp(l->buffer, "<<") == 0)
		t = TOK_HEREDOC;
	else if (ft_strcmp(l->buffer, ">>") == 0)
		t = TOK_APPEND;
	else if (l->state == LEXER_REDIR_IN)
		t = TOK_REDIR_IN;
	else
		t = TOK_REDIR_OUT;
	if (add_token(shell, l, t) == LEXER_ERROR)
		return (LEXER_ERROR);
	l->state = LEXER_DEFAULT;
	if ((t == TOK_REDIR_IN && c != '<') || (t == TOK_REDIR_OUT && c != '>'))
		return (handle_char(shell, l, c));
	return (handle_char(shell, l, c));
}
