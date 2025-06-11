/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_state_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 17:00:07 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/10 22:26:17 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_exit_status(t_mshell *shell, t_state *state, char **buffer)
{
	*buffer = ft_strdup_s(shell, "$?", MEM_TEMP);
	if (!buffer)
		return (1);
	if (add_token(shell, buffer, TOK_EXIT_STATUS))
		return (1);
	if (*state == STATE_IN_QUOTED_ENV)
		*state = STATE_IN_DOUBLE_QUOTE;
	else
		*state = STATE_DEFAULT;
	return (0);
}

int	handle_invalid_char(t_mshell *shell, t_state *state, char c, char **buffer)
{
	if (*buffer == NULL)
	{
		if (c == ' ')
		{
			if (append_char_to_buffer(shell, buffer, '$'))
				return (1);
			if (add_token(shell, buffer, TOK_WORD))
				return (1);
		}
		else
		{
			if (append_char_to_buffer(shell, buffer, '$'))
				return (1);
			if (append_char_to_buffer(shell, buffer, c))
				return (1);
		}
		if (*state == STATE_IN_QUOTED_ENV)
			*state = STATE_IN_DOUBLE_QUOTE;
		else
			*state = STATE_DEFAULT;
		return (0);
	}
	if (add_token(shell, buffer, TOK_ENV_VAR))
		return (1);
	if (*state == STATE_IN_QUOTED_ENV)
		*state = STATE_IN_DOUBLE_QUOTE;
	else
		*state = STATE_DEFAULT;
	if (handle_char(shell, state, c, buffer))
		return (1);
	return (0);
}
