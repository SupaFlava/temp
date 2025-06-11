/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_lexer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/10 22:33:04 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 02:15:05 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer_state handle_char(t_mshell *shell, t_lexer *l, char c)
{
	if (l->state == LEXER_DEFAULT)
		return (default_state(shell, l, c));
	else if (l->state == LEXER_SQUOTE)
		return (s_quote_state(shell, l, c));
	else if (l->state == LEXER_DQUOTE)
		return (d_quote_state(shell, l, c));
	else if (l->state == LEXER_ENV || l->state == LEXER_QUOTED_ENV)
		return (env_state(shell, l, c));
	else if (l->state == LEXER_REDIR_IN || l->state == LEXER_REDIR_OUT)
		return (redir_state(shell, l, c));
	return (LEXER_ERROR);
}

t_lexer_state	finalize_tokens(t_mshell *shell, t_lexer *l)
{
	t_toktype	type;

	if ((l->state == LEXER_ENV || l->state == LEXER_QUOTED_ENV) && !l->buffer)
	{
		if (!append_char_to_buffer(shell, l, '$'))
			return (LEXER_ERROR);
		l->state = (l->state == LEXER_QUOTED_ENV) ? LEXER_DQUOTE : LEXER_DEFAULT;
	}
	if (l->buffer)
	{
		type = find_token_type(l->buffer, l->state);
		if (!add_token(shell, l, type))
			return (LEXER_ERROR);
	}
	if (!check_quote_state(&l->state))
		return (LEXER_ERROR);
	return (l->state);
}



void	init_lexer(t_mshell *shell, t_lexer *l)
{
	ft_bzero(l, sizeof(t_lexer));
	l->input = shell->line;
	l->index = 0;
	l->state = LEXER_DEFAULT;
	l->buffer = NULL;
	l->tokens = NULL;
	l->c = 0;
}
static t_lexer_state process_line(t_mshell *shell, t_lexer *l)
{
	while (l->input[l->index])
	{
		char c = l->input[l->index];
		l->state = handle_char(shell, l, c);
		if (l->state == LEXER_ERROR)
			return (LEXER_ERROR);
		l->index++;
	}
	return (l->state);
}

t_token	*lexer(t_mshell *shell)
{
	t_lexer	*l;

	if (!shell->line || *(shell->line) == '\0')
		return (NULL);

	l = ft_malloc_s(shell, sizeof(t_lexer), MEM_TEMP);
	if (!l)
		return (NULL);
	init_lexer(shell, l);
	if (process_line(shell, l) == LEXER_ERROR)
		return (NULL);
	if (finalize_tokens(shell, l) == LEXER_ERROR)
		return (NULL);
	return (l->tokens);
}
