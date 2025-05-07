/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:59:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/07 22:09:09 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	handle_default_state(t_state *state, char c, char **buffer, t_token **tokens)
{
	if (c == ' ')
	{
		if (*buffer && **buffer)
		{
			add_token(tokens, *buffer, TOK_WORD);
			*buffer = NULL;
		}
	}
	else if (c == '\'')
	 	*state = STATE_IN_SINGLE_QUOTE;
	else if (c == '\"')
		*state = STATE_IN_DOUBLE_QUOTE;
	else if (c == '|')
		add_token(tokens, ft_strdup("|"), TOK_PIPE);
	else if (c == '<')
	{
		*state = STATE_IN_REDIR_IN;
		*buffer = 
	}
}