/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:47:24 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/16 14:02:14 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	add_token(t_mshell *shell, char *buffer, t_token_type type)
{
	t_token	*new;
	t_token	*last;

	if (!buffer || !*buffer)
		return (1);
	new = ft_malloc_s(shell, sizeof(t_token), MEM_TEMP);
	if (!new)
		return (1);
	new->content = ft_strndup(shell, buffer, ft_strlen(buffer));
	new->type = type;
	new->next = NULL;
	if (!shell->tokens)
		shell->tokens = new;
	else
	{
		last = shell->tokens;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	buffer = NULL;
	return (0);
}

t_token_type	find_token_type(const char *buffer, t_state state)
{
	if (ft_strcmp(buffer, "|") == 0)
		return (TOK_PIPE);
	else if (ft_strcmp(buffer, "<<") == 0)
		return (TOK_HEREDOC);
	else if (ft_strcmp(buffer, ">>") == 0)
		return (TOK_APPEND);
	else if (ft_strcmp(buffer, "<") == 0)
		return (TOK_REDIR_IN);
	else if (ft_strcmp(buffer, ">") == 0)
		return (TOK_REDIR_OUT);
	else if (ft_strcmp(buffer, "$?") == 0)
		return (TOK_EXIT_STATUS);
	else if (state == STATE_IN_ENV)
		return (TOK_ENV_VAR);
	else if (state == STATE_IN_SINGLE_QUOTE || state == STATE_IN_DOUBLE_QUOTE)
		return (TOK_QUOTED);
	else
		return (TOK_WORD);
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

int	handle_char(t_mshell *shell, t_state *state, char c, char **buffer)
{
	if (*state == STATE_DEFAULT)
		return (default_state(shell, state, c, buffer));
	else if (*state == STATE_IN_SINGLE_QUOTE)
		return (s_quote_state(shell, state, c, buffer));
	else if (*state == STATE_IN_DOUBLE_QUOTE)
		return (d_quote_state(shell, state, c, buffer));
	else if (*state == STATE_IN_ENV)
		return (env_state(shell, state, c, buffer));
	else if (*state == STATE_IN_REDIR_IN || *state == STATE_IN_REDIR_OUT)
		return (redir_state(shell, state, c, buffer));
	return (0);
}

t_token	*lexer(t_mshell *shell)
{
	t_state		state;
	size_t		i;
	char		*buffer;
	char		c;

	if (!shell->line || *(shell->line) == '\0')
		return (NULL);
	shell->tokens = NULL;//critical line, if not set to null: get invalid read/segfault
	state = STATE_DEFAULT;
	buffer = NULL;
	i = 0;
	while (shell->line[i])
	{
		c = shell->line[i];
		if (handle_char(shell, &state, c, &buffer))
			return (NULL);//error occured - break lexer process here
		i++;
	}
	if (buffer && *buffer)
	{
		if (add_token(shell, buffer, find_token_type(buffer, state)))
			return (NULL);//error on last token
	}
	if (state == STATE_IN_DOUBLE_QUOTE || state == STATE_IN_SINGLE_QUOTE)
	{
		ft_printf("SYNTAX ERROR, no closing quote found.\n");//return because unclosed quotes
		return (NULL);
	}
	ft_printf("registered tokens:\n");
	return (shell->tokens);//succes
}
