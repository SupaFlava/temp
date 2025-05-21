/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_state_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:45:43 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/20 16:28:39 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_redir_in(t_mshell *shell, char **buf, t_state *state)
{
	if (flush_set_state(shell, buf, state, STATE_IN_REDIR_IN))
		return (1);
	return (set_buf_to_char(shell, buf, '<'));
}

int	handle_redir_out(t_mshell *shell, char **buf, t_state *state)
{
	if (flush_set_state(shell, buf, state, STATE_IN_REDIR_OUT))
		return (1);
	return (set_buf_to_char(shell, buf, '>'));
}
