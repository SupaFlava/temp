/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_redir_state_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 00:45:21 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 01:58:49 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer_state	handle_redir_in(t_mshell *shell, t_lexer *l)
{
	if (!flush_set_state(shell, l, LEXER_REDIR_IN))
		return (LEXER_ERROR);
	return set_buf_to_char(shell, l, '<');
}

t_lexer_state	handle_redir_out(t_mshell *shell, t_lexer *l)
{
	if (!flush_set_state(shell, l, LEXER_REDIR_OUT))
		return (LEXER_ERROR);
	return set_buf_to_char(shell, l, '>');
}
