/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 19:08:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/20 16:47:14 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_char(t_mshell *shell, t_state *state, char c, char **buffer)
{
	if (*state == STATE_DEFAULT)
		return (default_state(shell, state, c, buffer));
	else if (*state == STATE_IN_SINGLE_QUOTE)
		return (s_quote_state(shell, state, c, buffer));
	else if (*state == STATE_IN_DOUBLE_QUOTE)
		return (d_quote_state(shell, state, c, buffer));
	else if (*state == STATE_IN_ENV || *state == STATE_IN_QUOTED_ENV)
		return (env_state(shell, state, c, buffer));
	else if (*state == STATE_IN_REDIR_IN || *state == STATE_IN_REDIR_OUT)
		return (redir_state(shell, state, c, buffer));
	return (0);
}

int	finalize_tokens(t_mshell *shell, t_state *state, char **buffer)
{
	if (buffer && *buffer)
	{
		if (add_token(shell, buffer, find_token_type(*buffer, *state)))
			return (1);
	}
	if (check_quote_state(state))
		return (1);
	return (0);
}

void	init_lexer(t_mshell *shell, t_state *state, char **buffer)
{
	shell->tokens = NULL;
	*state = STATE_DEFAULT;
	*buffer = NULL;
}

int	process_line_loop(t_mshell *shell, t_state *state, char **buffer)
{
	size_t	i;
	char	c;

	i = 0;
	while (shell->line[i])
	{
		c = shell->line[i];
		if (handle_char(shell, state, c, buffer))
			return (1);
		i++;
	}
	return (0);
}

t_token	*lexer(t_mshell *shell)
{
	t_state		state;
	char		*buffer;

	if (!shell->line || *(shell->line) == '\0')
		return (NULL);
	init_lexer(shell, &state, &buffer);
	if (process_line_loop(shell, &state, &buffer))
		return (NULL);
	if (finalize_tokens(shell, &state, &buffer))
		return (NULL);
	return (shell->tokens);
}
