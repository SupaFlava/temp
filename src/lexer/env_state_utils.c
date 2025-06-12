/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_state_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 17:00:07 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/12 15:05:37 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


t_lexer_state	flush_non_env_token(t_mshell *s, t_lexer *l, t_toktype type)
{
	if (add_token(s, l, type) == LEXER_ERROR)
		return (LEXER_ERROR);
	if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
	else
		l->state = LEXER_DEFAULT;
	return (l->state);
}

t_lexer_state	handle_exit_status(t_mshell *shell, t_lexer *l)
{
	l->buffer = ft_strdup_s(shell, "$?", MEM_TEMP);
	if (!l->buffer)
		return (LEXER_ERROR);
	if (add_token(shell, l, TOK_EXIT_STATUS) == LEXER_ERROR)
		return (LEXER_ERROR);
	if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
	else
		l->state = LEXER_DEFAULT;
	return (l->state);
}

t_lexer_state	handle_invalid_env(t_mshell *shell, t_lexer *l, char c)
{
	if (!l->buffer)
	{
		if (append_char_to_buffer(shell, l, '$') == LEXER_ERROR)
			return (LEXER_ERROR);
		if (append_char_to_buffer(shell, l, c) == LEXER_ERROR)
			return (LEXER_ERROR);
		if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
		else
		l->state = LEXER_DEFAULT;
		return (l->state);
	}
	if (add_token(shell, l, TOK_ENV_VAR) == LEXER_ERROR)
		return (LEXER_ERROR);
	if (l->state == LEXER_QUOTED_ENV)
		l->state = LEXER_DQUOTE;
	else
		l->state = LEXER_DEFAULT;
	return (handle_char(shell, l, c));
}
