/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_state_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:45:43 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 19:02:12 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer_state	handle_redir_in(t_mshell *shell, t_lexer *l)
{
	if (flush_set_state(shell, l, LEXER_REDIR_IN) == LEXER_ERROR)
		return (LEXER_ERROR);
	return (set_buf_to_char(shell, l, '<'));
}

t_lexer_state	handle_redir_out(t_mshell *shell, t_lexer *l)
{
	if (flush_set_state(shell, l, LEXER_REDIR_OUT) == LEXER_ERROR)
		return (LEXER_ERROR);
	return (set_buf_to_char(shell, l, '>'));
}
