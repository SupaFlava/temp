/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 14:49:32 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/19 17:06:31 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

const char	*token_type_to_string(t_token_type type)
{
	if (type == TOK_WORD)
		return ("WORD");
	if (type == TOK_QUOTED)
		return ("QUOTED");
	if (type == TOK_PIPE)
		return ("PIPE");
	if (type == TOK_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOK_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOK_HEREDOC)
		return ("HEREDOC");
	if (type == TOK_APPEND)
		return ("APPEND");
	if (type == TOK_ENV_VAR)
		return ("ENV_VAR");
	if (type == TOK_EXIT_STATUS)
		return ("EXIT_STATUS");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	ft_printf("registered tokens:\n");
	while (tokens)
	{
		ft_printf("Token: %s | type %s\n", (char *)tokens->content, token_type_to_string(tokens->type));
		tokens = tokens->next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		if (tokens->content)
			free(tokens->content);
		free (tokens);
		tokens = temp;
	}
}
