/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:59:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/20 17:10:58 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	default_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	if (c == ' ')
		return (add_token(shell, buffer, TOK_WORD));
	else if (c == '\'')
		return (flush_set_state(shell, buffer, state, STATE_IN_SINGLE_QUOTE));
	else if (c == '\"')
		return (flush_set_state(shell, buffer, state, STATE_IN_DOUBLE_QUOTE));
	else if (c == '|')
		return (flush_set_buf(shell, buffer, "|", TOK_PIPE));
	else if (c == '<')
		return (handle_redir_in(shell, buffer, state));
	else if (c == '>')
		return (handle_redir_out(shell, buffer, state));
	else if (c == '$')
		*state = STATE_IN_ENV;
	else
		return (append_char_to_buffer(shell, buffer, c));
	return (0);
}

int	s_quote_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	if (c == '\'')
	{
		*state = STATE_DEFAULT;
		if (add_token (shell, buffer, TOK_QUOTED))
			return (1);
	}
	else
		return (append_char_to_buffer(shell, buffer, c));
	return (0);
}

int	d_quote_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	if (c == '"')
	{
		*state = STATE_DEFAULT;
		if (*buffer != NULL)
		{
			if (add_token(shell, buffer, TOK_QUOTED))
				return (1);
		}
	}
	else if (c == '$')
	{
		if (*buffer != NULL)
		{
			if (add_token(shell, buffer, TOK_QUOTED))
				return (1);
		}
		*state = STATE_IN_QUOTED_ENV;
	}
	else
		return (append_char_to_buffer(shell, buffer, c));
	return (0);
}

int	env_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	if (c == '?' && !*buffer)
		return (handle_exit_status(shell, state, buffer));
	else if (!ft_isalnum(c) && c != '_')
		return (handle_invalid_char(shell, state, c, buffer));
	else if (append_char_to_buffer(shell, buffer, c))
		return (1);
	return (0);
}

int	redir_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	t_toktype	t;

	if ((*state == STATE_IN_REDIR_IN && c == '<')
		|| (*state == STATE_IN_REDIR_OUT && c == '>'))
	{
		if (append_char_to_buffer(shell, buffer, c))
			return (1);
	}
	if (ft_strcmp(*buffer, "<<") == 0)
		t = TOK_HEREDOC;
	else if (ft_strcmp(*buffer, ">>") == 0)
		t = TOK_APPEND;
	else if (*state == STATE_IN_REDIR_IN)
		t = TOK_REDIR_IN;
	else
		t = TOK_REDIR_OUT;
	if (add_token(shell, buffer, t))
		return (1);
	*state = STATE_DEFAULT;
	if ((t == TOK_REDIR_IN && c != '<') || (t == TOK_REDIR_OUT && c != '>'))
	{
		if (handle_char(shell, state, c, buffer))
			return (1);
	}
	return (0);
}
