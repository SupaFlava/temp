/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_state_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 17:00:07 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/07 22:43:26 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_valid_env(char *buffer)
{
	int	i;

	i = 0;
	if (!ft_isalpha(buffer[0]) && buffer[0] != '_')
		return (0);
	while (buffer[i])
	{
		if (!ft_isalnum(buffer[i]) && buffer[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_lexstate	handle_exit_status(t_mshell *shell, t_lexer *l)
{
	char	*new_str;
	char	*num;

	num = ft_itoa(shell->exit_status);
	if (!l->buffer)
	{
		l->buffer = ft_strdup_s(shell, num, MEM_TEMP);
		if (!l->buffer)
			return (LEXER_ERROR);
	}
	else
	{
		new_str = ft_strjoin_s(l->buffer, num, shell, MEM_TEMP);
		if (!new_str)
			return (LEXER_ERROR);
		l->buffer = ft_strdup_s(shell, new_str, MEM_TEMP);
		if (!l->buffer)
			return (LEXER_ERROR);
	}
	if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
	else
		l->state = LEXER_DEFAULT;
	return (l->state);
}

t_lexstate	handle_empty_buffer_env(t_mshell *shell, t_lexer *l, char c)
{
	if (append_char_to_buffer(shell, l, '$') == LEXER_ERROR)
		return (LEXER_ERROR);
	if (c == '"' || c == '\'')
	{
		if (l->state == LEXER_QUOTED_ENV)
			l->state = LEXER_DQUOTE;
		else
		{
			if (flush_set_state(shell, l, LEXER_DEFAULT) == LEXER_ERROR)
				return (LEXER_ERROR);
			return (handle_char(shell, l, c));
		}
		return (handle_char(shell, l, c));
	}
	if (append_char_to_buffer(shell, l, c) == LEXER_ERROR)
		return (LEXER_ERROR);
	if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
	else
		l->state = LEXER_DEFAULT;
	return (l->state);
}

t_lexstate	handle_invalid_env(t_mshell *shell, t_lexer *l, char c)
{
	if (!l->buffer)
		return (handle_empty_buffer_env(shell, l, c));
	if (c == '$' && !is_valid_env(l->buffer))
		return (append_char_to_buffer(shell, l, c));
	if (is_valid_env(l->buffer))
	{
		if (add_token(shell, l, TOK_ENV_VAR) == LEXER_ERROR)
			return (LEXER_ERROR);
	}
	if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
	else
		l->state = LEXER_DEFAULT;
	return (handle_char(shell, l, c));
}
