/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 13:39:05 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/02 15:17:48 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexstate	check_quote_state(t_lexstate state)
{
	if (state == LEXER_DQUOTE
		|| state == LEXER_SQUOTE
		|| state == LEXER_QUOTED_ENV)
	{
		print_err("minishell", "syntax error", "no closing quote found");
		return (LEXER_ERROR);
	}
	return (LEXER_DEFAULT);
}

t_lexstate	append_char_to_buffer(t_mshell *shell, t_lexer *l, char c)
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

t_lexstate	flush_set_state(t_mshell *sh, t_lexer *l, t_lexstate new_state)
{
	if (l->buffer && *l->buffer)
	{
		if (add_token(sh, l, TOK_WORD) == LEXER_ERROR)
			return (LEXER_ERROR);
	}
	if (new_state == LEXER_DQUOTE)
		start_new_quote_group(l);
	l->state = new_state;
	return (l->state);
}

t_lexstate	flush_set_buf(t_mshell *sh, t_lexer *l, const char *s, t_toktype t)
{
	if (add_token(sh, l, TOK_WORD) == LEXER_ERROR)
		return (LEXER_ERROR);
	l->buffer = ft_strdup_s(sh, s, MEM_TEMP);
	if (!l->buffer)
		return (LEXER_ERROR);
	if (add_token(sh, l, t) == LEXER_ERROR)
		return (LEXER_ERROR);
	l->buffer = NULL;
	return (l->state);
}

t_lexstate	set_buf_to_char(t_mshell *shell, t_lexer *l, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	l->buffer = ft_strdup_s(shell, temp, MEM_TEMP);
	if (!l->buffer)
		return (LEXER_ERROR);
	return (l->state);
}
