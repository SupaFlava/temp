/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_state_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:45:43 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/06/28 10:29:25 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexstate	handle_redir_in(t_mshell *shell, t_lexer *l)
{
	if (flush_set_state(shell, l, LEXER_REDIR_IN) == LEXER_ERROR)
		return (LEXER_ERROR);
	return (set_buf_to_char(shell, l, '<'));
}

t_lexstate	handle_redir_out(t_mshell *shell, t_lexer *l)
{
	if (flush_set_state(shell, l, LEXER_REDIR_OUT) == LEXER_ERROR)
		return (LEXER_ERROR);
	return (set_buf_to_char(shell, l, '>'));
}
