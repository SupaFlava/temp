/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_lexer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 00:37:20 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 02:26:44 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_quote_state(t_lexer_state *state)
{
	if (*state == LEXER_DQUOTE || *state == LEXER_SQUOTE)
	{
		ft_printf("no closing quote found, SYNTAX ERROR\n");
		return (0);
	}
	return (1);
}

int	append_char_to_buffer(t_mshell *shell, t_lexer *l, char c)
{
	size_t	len;
	char	*new_buffer;

	if (l->buffer)
		len = ft_strlen(l->buffer);
	else
		len = 0;
	new_buffer = ft_malloc_s(shell, len + 2, MEM_TEMP);
	if (!new_buffer)
		return (0);
	if (l->buffer)
		ft_strcpy(new_buffer, l->buffer);
	else
		new_buffer[0] = '\0';
	new_buffer[len] = c;
	new_buffer[len + 1] = '\0';
	l->buffer = new_buffer;
	return (1);
}

int flush_set_state(t_mshell *shell, t_lexer *l, t_lexer_state new_state)
{
	if (!add_token(shell, l, TOK_WORD))
		return (0);
	l->state = new_state;
	return (1);
}

t_lexer_state flush_set_buf(t_mshell *shell, t_lexer *l, const char *s, t_toktype type)
{
	if (!add_token(shell, l, TOK_WORD))
		return (LEXER_ERROR);
	l->buffer = ft_strdup_s(shell, s, MEM_TEMP);
	if (!l->buffer)
		return (LEXER_ERROR);
	if (!add_token(shell, l, type))
		return (LEXER_ERROR);
	l->buffer = NULL;
	return (LEXER_DEFAULT);
}

t_lexer_state	set_buf_to_char(t_mshell *shell, t_lexer *l, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	l->buffer = ft_strdup_s(shell, temp, MEM_TEMP);
	if (!l->buffer)
		return (LEXER_ERROR);
	if (c == '<')
		return (LEXER_REDIR_IN);
	else if (c == '>')
		return (LEXER_REDIR_OUT);
	return (LEXER_ERROR);
}
