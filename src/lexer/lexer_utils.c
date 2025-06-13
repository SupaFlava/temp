/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 13:39:05 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 19:08:42 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer_state	check_quote_state(t_lexer_state state)
{
	if (state == LEXER_DQUOTE || state == LEXER_SQUOTE)
	{
		ft_printf("no closing quote found, SYNTAX ERROR\n");
		return (LEXER_ERROR);
	}
	return (LEXER_DEFAULT);
}

t_lexer_state	append_char_to_buffer(t_mshell *shell, t_lexer *l, char c)
{
	size_t	len;
	char	*new_buffer;

	if (l->buffer)
		len = ft_strlen(l->buffer);
	else
		len = 0;
	new_buffer = ft_malloc_s(shell, (len + 2), MEM_TEMP);
	if (!new_buffer)
		return (LEXER_ERROR);
	if (l->buffer)
		ft_strcpy(new_buffer, l->buffer);
	else
		new_buffer[0] = '\0';
	new_buffer[len] = c;
	new_buffer[len + 1] = '\0';
	l->buffer = new_buffer;
	return (l->state);
}

t_lexer_state	flush_set_state(t_mshell *sh, t_lexer *l, t_lexer_state new_state)
{
	if (l->buffer && *l->buffer)
	{
		if (!add_token(sh, l, TOK_WORD))
			return (LEXER_ERROR);
	}
		l->state = new_state;
		return (l->state);
}

t_lexer_state	flush_set_buf(t_mshell *sh, t_lexer *l, const char *s, t_toktype type)
{
	if (add_token(sh, l, TOK_WORD) == LEXER_ERROR)
		return (LEXER_ERROR);
	l->buffer = ft_strdup_s(sh, s, MEM_TEMP);
	if (!l->buffer)
		return (LEXER_ERROR);
	if (add_token(sh, l, type) == LEXER_ERROR)
		return (LEXER_ERROR);
	l->buffer = NULL;
	return (l->state);
}

t_lexer_state	set_buf_to_char(t_mshell *shell, t_lexer *l, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	l->buffer = ft_strdup_s(shell, temp, MEM_TEMP);
	if (!l->buffer)
		return (LEXER_ERROR);
	return (l->state);
}
