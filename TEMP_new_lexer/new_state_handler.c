/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_state_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/10 23:42:28 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 02:07:53 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer_state default_state(t_mshell *shell, t_lexer *l, char c)
{
	if (c == ' ')
	{
		if (l->buffer && !add_token(shell, l, TOK_WORD))
			return (LEXER_ERROR);
		return (LEXER_DEFAULT);
	}
	else if (c == '\'')
	{
		if (l->buffer && !add_token(shell, l, TOK_WORD))
			return (LEXER_ERROR);
		return (LEXER_SQUOTE);
	}
	else if (c == '"')
	{
		if (l->buffer && !add_token(shell, l, TOK_WORD))
			return (LEXER_ERROR);
		return (LEXER_DQUOTE);
	}
	else if (c == '|')
		return (flush_set_buf(shell, l, "|", TOK_PIPE));
	else if (c == '<')
		return (handle_redir_in(shell, l));
	else if (c == '>')
		return (handle_redir_out(shell, l));
	else if (c == '$')
		return (LEXER_ENV);
	else
	{
		if (!append_char_to_buffer(shell, l, c))
			return (LEXER_ERROR);
		return (LEXER_DEFAULT);
	}
}

t_lexer_state s_quote_state(t_mshell *shell, t_lexer *l, char c)
{
	if (c == '\'')
	{
		if (!add_token(shell, l, TOK_QUOTED))
			return (LEXER_ERROR);
		return (LEXER_DEFAULT);
	}
	else
	{
		if (!append_char_to_buffer(shell, l, c))
			return (LEXER_ERROR);
		return (LEXER_SQUOTE);
	}
}

t_lexer_state d_quote_state(t_mshell *shell, t_lexer *l, char c)
{
	if (c == '"')
	{
		if (l->buffer)
			if (!add_token(shell, l, TOK_QUOTED))
				return (LEXER_ERROR);
		return (LEXER_DEFAULT);
	}
	else if (c == '$')
	{
		if (l->buffer)
			if (!add_token(shell, l, TOK_QUOTED))
				return (LEXER_ERROR);
		return (LEXER_QUOTED_ENV);
	}
	else
	{
		if (!append_char_to_buffer(shell, l, c))
			return (LEXER_ERROR);
		return (LEXER_DQUOTE);
	}
}

t_lexer_state env_state(t_mshell *shell, t_lexer *l, char c)
{
	if (l->state == LEXER_QUOTED_ENV && c == '"' && !l->buffer)
	{
		if (!append_char_to_buffer(shell, l, '$'))
			return (LEXER_ERROR);
		return (LEXER_DQUOTE);
	}
	if (c == '?' && !l->buffer)
		return (handle_exit_status(shell, l));
	if (!ft_isalnum(c) && c != '_')
		return (handle_invalid_char(shell, l, c));
	if (!append_char_to_buffer(shell, l, c))
		return (LEXER_ERROR);
	return (l->state);
}

t_lexer_state redir_state(t_mshell *shell, t_lexer *l, char c)
{
	t_toktype t;

	if ((l->state == LEXER_REDIR_IN && c == '<')
		|| (l->state == LEXER_REDIR_OUT && c == '>'))
	{
		if (append_char_to_buffer(shell, l, c))
			return (LEXER_ERROR);
	}
	if (ft_strcmp(l->buffer, "<<") == 0)
		t = TOK_HEREDOC;
	else if (ft_strcmp(l->buffer, ">>") == 0)
		t = TOK_APPEND;
	else if (l->state == LEXER_REDIR_IN)
		t = TOK_REDIR_IN;
	else
		t = TOK_REDIR_OUT;

	if (add_token(shell, l, t))
		return (LEXER_ERROR);

	if ((t == TOK_REDIR_IN && c != '<') || (t == TOK_REDIR_OUT && c != '>'))
		return (handle_char(shell, l, c));

	return (LEXER_DEFAULT);
}
