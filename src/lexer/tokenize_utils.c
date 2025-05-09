/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 12:59:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/09 18:14:02 by jbaetsen      ########   odam.nl         */
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
		*buffer = ft_strndup(&c, 1);
	}
	else if (c == '>')
	{
		*state = STATE_IN_REDIR_OUT;
		*buffer = ft_strndup(&c, 1);
	}
	else if (c == '$')
		*state = STATE_IN_ENV;
	else
		append_char_to_buffer(buffer, c);
}

void	handle_single_quote(t_state *state, char c, char **buffer, t_token **tokens)
{
	if (c == '\'')
	{
		*state = STATE_DEFAULT;
		add_token (tokens, *buffer, TOK_QUOTED);
		*buffer = NULL;
	}
	else
		append_char_to_buffer(buffer, c);
}

void	handle_double_quote(t_state *state, char c, char **buffer, t_token **tokens)
{
	if (c == '"')
	{
		*state = STATE_DEFAULT;
		add_token(tokens, *buffer, TOK_QUOTED);
		*buffer = NULL;
	}
	else
		append_char_to_buffer(buffer, c);
}

void	handle_env_state(t_state *state, char c, char **buffer, t_token **tokens)
{
	t_token_type	type;

	if (!ft_isalnum(c) && c != '_')
	{
		if (ft_strncmp(*buffer, "?", ft_strlen(*buffer)))
			type = TOK_EXIT_STATUS;
		else
			type = TOK_ENV_VAR;
		add_token(tokens, *buffer, type);
		*buffer = NULL;
		*state = STATE_DEFAULT;

		handle_char(state, c, buffer, tokens);
	}
	else
		append_char_to_buffer(buffer, c);
}

void	handle_redir_state(t_state *state, char c, char **buffer, t_token **tokens)
{
	t_token_type type;

	if ((*state == STATE_IN_REDIR_IN && c == '<') ||
		(*state == STATE_IN_REDIR_OUT && c == '>'))
			append_char_to_buffer(buffer, c);

	if (ft_strcmp(*buffer, "<<") == 0)
		type = TOK_HEREDOC;
	else if (ft_strcmp(*buffer, ">>") == 0)
		type = TOK_APPEND;
	else if (*state == STATE_IN_REDIR_IN)
		type = TOK_REDIR_IN;
	else
		type = TOK_REDIR_OUT;
	add_token(tokens, *buffer, type);
	*buffer = NULL;
	*state = STATE_DEFAULT;
	if ((type == TOK_REDIR_IN && c != '<') || (type == TOK_REDIR_OUT && c != '>'))
		handle_char(state, c, buffer, tokens);
}
