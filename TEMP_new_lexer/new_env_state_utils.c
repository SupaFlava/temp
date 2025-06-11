/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_env_state_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 00:46:36 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 02:03:37 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer_state	handle_exit_status(t_mshell *shell, t_lexer *l)
{
	l->buffer = ft_strdup_s(shell, "$?", MEM_TEMP);
	if (!l->buffer)
		return (LEXER_ERROR);
	if (!add_token(shell, l, TOK_EXIT_STATUS))
		return (LEXER_ERROR);
	if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
	else
		l->state = LEXER_DEFAULT;
	return (l->state);
}

t_lexer_state	handle_invalid_char(t_mshell *shell, t_lexer *l, char c)
{
	if (!l->buffer)
	{
		if (c == ' ')
		{
			if (!append_char_to_buffer(shell, l, '$'))
				return (LEXER_ERROR);
			if (!add_token(shell, l, TOK_WORD))
				return (LEXER_ERROR);
		}
		else
		{
			if (!append_char_to_buffer(shell, l, '$'))
				return (LEXER_ERROR);
			if (!append_char_to_buffer(shell, l, c))
				return (LEXER_ERROR);
		}
		if (l->state == LEXER_QUOTED_ENV)
			l->state = LEXER_DQUOTE;
		else
			l->state = LEXER_DEFAULT;
		return (l->state);
	}
	if (!add_token(shell, l, TOK_ENV_VAR))
		return (LEXER_ERROR);
	if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
	else
		l->state = LEXER_DEFAULT;
	l->state = handle_char(shell, l, c);
	if (l->state == LEXER_ERROR)
		return (LEXER_ERROR);
	return (l->state);
}
