/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 13:39:05 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/11 02:31:44 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_quote_state(t_state *state)
{
	if (*state == STATE_IN_DOUBLE_QUOTE || *state == STATE_IN_SINGLE_QUOTE)
	{
		ft_printf("no closing quote found, SYNTAX ERROR\n");
		return (1);
	}
	return (0);
}

int	append_char_to_buffer(t_mshell *shell, char **buffer, char c)
{
	size_t	len;
	char	*new_buffer;

	if (buffer != NULL)
		len = ft_strlen(*buffer);
	else
		len = 0;
	new_buffer = ft_malloc_s(shell, (len + 2), MEM_TEMP);
	if (!new_buffer)
		return (1);
	if (*buffer != NULL)
		ft_strcpy(new_buffer, *buffer);
	else
		new_buffer[0] = '\0';
	new_buffer[len] = c;
	new_buffer[len + 1] = '\0';
	*buffer = new_buffer;
	return (0);
}

int	flush_set_state(t_mshell *sh, char **buf, t_state *state, t_state n_state)
{
	if (add_token(sh, buf, TOK_WORD))
		return (1);
	*state = n_state;
	return (0);
}

int	flush_set_buf(t_mshell *sh, char **buf, const char *s, t_toktype type)
{
	if (add_token(sh, buf, TOK_WORD))
		return (1);
	*buf = ft_strdup_s(sh, s, MEM_TEMP);
	if (!*buf)
		return (1);
	if (add_token(sh, buf, type))
		return (1);
	*buf = NULL;
	return (0);
}

int	set_buf_to_char(t_mshell *shell, char **buf, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	*buf = ft_strdup_s(shell, temp, MEM_TEMP);
	return (*buf == NULL);
}
