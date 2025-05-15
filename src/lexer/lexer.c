/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:47:24 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/15 12:09:43 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	add_token(t_token **tokens, char *buffer, t_token_type type)
{
	t_token *new;
	t_token *temp;
	if (!buffer || !*buffer)
		return ;
	new = malloc(sizeof(t_token));
	if (!new)
		return;

	new->content = ft_strdup(buffer);
	new->type = type;
	new->next = NULL;

	if (*tokens == NULL)
		*tokens = new;
	else
	{
		temp = *tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}	
	free (buffer);
	buffer = NULL;
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

void	append_char_to_buffer(char **buffer, char c)
{
	size_t 	len;
	char	*new_buffer;

	if (buffer != NULL)
		len = ft_strlen(*buffer);
	else
		len = 0;
	new_buffer = malloc(len + 2); // +1 for the next char, +1 for the null terminator
	if (!new_buffer)
		return ;

	if (*buffer != NULL)
	{
		ft_strcpy(new_buffer, *buffer);
		free(*buffer);
	}
	else
		new_buffer[0] = '\0';
	new_buffer[len] = c;
	new_buffer[len + 1] = '\0';
	*buffer = new_buffer;	
}

void	handle_char(t_state *state, char c, char **buffer, t_token **tokens)
{
	if (*state == STATE_DEFAULT)
		handle_default_state(state, c, buffer, tokens);
	else if (*state == STATE_IN_SINGLE_QUOTE)
		handle_single_quote(state, c, buffer, tokens);
	else if (*state == STATE_IN_DOUBLE_QUOTE)
		handle_double_quote(state, c, buffer, tokens);
	else if (*state == STATE_IN_ENV)
		handle_env_state(state, c, buffer, tokens);
	else if (*state == STATE_IN_REDIR_IN || *state == STATE_IN_REDIR_OUT)
		handle_redir_state(state, c, buffer, tokens);
}

t_token *lexer(const char *input)
{
	t_token		*tokens;
	t_state		state;
	size_t		i;
	char		*buffer; // Will hold the current token string.
	char		c;
	if (!input || *input == '\0')
		return (NULL);
	tokens = NULL;
	state = STATE_DEFAULT;
	buffer = NULL;
	i = 0;
	while (input[i])
	{
		c = input[i];
		// Call a helper to handle transitions and token building
		handle_char(&state, c, &buffer, &tokens);
		i++;
	}

	// Flush the final token if needed
	if (buffer && *buffer)
		add_token(&tokens, buffer, find_token_type(buffer, state));

	return (tokens);
}
