/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:47:24 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/08 12:01:43 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	handle_char(t_state *state, char c, char **buffer, t_token tokens)
{
	if (*state == STATE_DEFAULT)
		handle_default_state(state, c, buffer, tokens);
	else if (*state == STATE_IN_SINGLE_QUOTE)
		handle_single_quote_state(state, c, buffer, tokens);
	else if (*state == STATE_IN_DOUBLE_QUOTE)
		handle_double_quote_state(state, c, buffer, tokens);
	else if (*state == STATE_IN_ENV)
		handle_env_state(state, c, buffer, tokens);

}

t_token *lexer(const char *input)
{
	t_token		*head = NULL;
	t_state		state = STATE_DEFAULT;
	size_t		i = 0;
	char		*buffer = NULL; // Will hold the current token string.
	char		c;

	head = NULL;
	state = STATE_DEFAULT;
	i = 0;
	while (input[i])
	{
		c = input[i];
		// Call a helper to handle transitions and token building
		handle_char(&state, c, &buffer, *head);
		i++;
	}

	// Flush the final token if needed
	if (buffer && *buffer)
		add_token(&head, buffer, resolve_token_type(state));

	return head;
}
