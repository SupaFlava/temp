/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/02 13:18:49 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/07 22:04:30 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	finalize_tokens(t_mshell *shell, t_lexer *l)
{
	t_toktype	type;

	type = TOK_WORD;
	if (check_quote_state(l->state) == LEXER_ERROR)
		return (0);
	if (l->state == LEXER_ENV)
	{
		if (!l->buffer || !is_valid_env(l->buffer))
		{
			if (append_char_to_buffer(shell, l, '$') == LEXER_ERROR)
				return (0);
			l->state = LEXER_DEFAULT;
		}
	}
	if (l->buffer)
	{
		type = find_token_type(l->buffer, l->state);
		if (add_token(shell, l, type) == LEXER_ERROR)
			return (0);
	}
	return (1);
}

int	validate_tokens(t_lexer *l)
{
	t_token	*last;

	last = l->tokens;
	while (last && last->next)
		last = last->next;
	if (last && last->type == TOK_PIPE)
		return (0);
	return (1);
}
