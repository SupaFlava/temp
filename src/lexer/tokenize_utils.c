/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:59:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/19 14:34:27 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	default_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	char	temp[2];//temp is required for ft_strndup, if you pass &c to ft_strndup you get a stack_overflow, cause char c doesnt have '\0'

	temp[0] = c;
	temp[1] = '\0';
	if (c == ' ')
	{
		if (*buffer && **buffer)
		{
			if (add_token(shell, *buffer, TOK_WORD))
				return (1);
			*buffer = NULL;
		}
	}
	else if (c == '\'')
		*state = STATE_IN_SINGLE_QUOTE;
	else if (c == '\"')
		*state = STATE_IN_DOUBLE_QUOTE;
	else if (c == '|')
	{
		if (*buffer != NULL)
		{
			if (add_token(shell, *buffer, TOK_WORD))
				return (1);
			*buffer = NULL;
		}
		if (add_token(shell, ft_strndup(shell, "|", 1), TOK_PIPE)) //if add_token fails(returns1), this func also returns 1
			return (1);
	}
	else if (c == '<')
	{
		if (*buffer != NULL)
		{
			if (add_token(shell, *buffer, TOK_WORD))
				return (1);
			*buffer = NULL;
		}
		*state = STATE_IN_REDIR_IN;
		*buffer = ft_strndup(shell, temp, 1);
		if (!*buffer)
			return (1);
	}
	else if (c == '>')
	{
		if (*buffer != NULL)
		{
			if (add_token(shell, *buffer, TOK_WORD))
				return (1);
			*buffer = NULL;
		}
		*state = STATE_IN_REDIR_OUT;
		*buffer = ft_strndup(shell, temp, 1);
		if (!*buffer)
			return (1);
	}
	else if (c == '$')
		*state = STATE_IN_ENV;
	else
		return (append_char_to_buffer(shell, buffer, c)); // returns  the return value of append_char 1 on fail, 0 on succes.
	return (0);
}

int	s_quote_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	if (c == '\'')
	{
		*state = STATE_DEFAULT;
		if (add_token (shell, *buffer, TOK_QUOTED))
			return (1);
		*buffer = NULL;
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
		if (add_token(shell, *buffer, TOK_QUOTED))
			return (1);
		*buffer = NULL;
	}
	else
		return (append_char_to_buffer(shell, buffer, c));
	return (0);
}

int	env_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	t_token_type	type;

	if (!ft_isalnum(c) && c != '_')
	{
		if (ft_strncmp(*buffer, "?", ft_strlen(*buffer)))
			type = TOK_EXIT_STATUS;
		else
			type = TOK_ENV_VAR;
		if (add_token(shell, *buffer, type))
			return (1);
		*buffer = NULL;
		*state = STATE_DEFAULT;
		if (handle_char(shell, state, c, buffer))
			return (1);
	}
	else if (append_char_to_buffer(shell, buffer, c))
		return (1);
	return (0);
}

int	redir_state(t_mshell *shell, t_state *state, char c, char **buffer)
{
	t_token_type	type;

	if ((*state == STATE_IN_REDIR_IN && c == '<')
		|| (*state == STATE_IN_REDIR_OUT && c == '>'))
	{
		if (append_char_to_buffer(shell, buffer, c))
			return (1);
	}
	if (ft_strcmp(*buffer, "<<") == 0)
		type = TOK_HEREDOC;
	else if (ft_strcmp(*buffer, ">>") == 0)
		type = TOK_APPEND;
	else if (*state == STATE_IN_REDIR_IN)
		type = TOK_REDIR_IN;
	else
		type = TOK_REDIR_OUT;
	if (add_token(shell, *buffer, type))
		return (1);
	*buffer = NULL;
	*state = STATE_DEFAULT;
	if ((type == TOK_REDIR_IN && c != '<')
		|| (type == TOK_REDIR_OUT && c != '>'))
	{
		if (handle_char(shell, state, c, buffer))
			return (1);
	}
	return (0);
}
