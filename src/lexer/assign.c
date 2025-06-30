/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 11:34:59 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/30 14:22:37 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexstate	handle_assign_state(t_mshell *shell, t_lexer *l, char c)
{
	if (!l->buffer || !*l->buffer)
		return (LEXER_DEFAULT);
	if (append_char_to_buffer(shell, l, c))
		return (LEXER_ERROR);
	if (l->buffer && is_valid_export(l->buffer))
		return (LEXER_ASSIGN);
	return (LEXER_DEFAULT);
}

t_lexstate	assign_state(t_mshell *shell, t_lexer *l, char c)
{
	static bool	in_squote = false;
	static bool	in_dquote = false;

	if (c == '\'' && !in_dquote)
	{
		in_squote = !in_squote;
		return (LEXER_ASSIGN);
	}
	else if (c == '"' && !in_squote)
	{
		in_dquote = !in_dquote;
		return (LEXER_ASSIGN);
	}
	else if (c == ' ' && !in_squote && !in_dquote)
	{
		in_squote = false;
		in_dquote = false;
		l->state = LEXER_DEFAULT;
		return (add_token(shell, l, TOK_ASSIGN));
	}
	else
		return (append_char_to_buffer(shell, l, c));
}
