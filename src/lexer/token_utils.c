/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 16:36:46 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/13 16:45:16 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_toktype	find_token_type(const char *buffer, t_lexstate state)
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
	else if (state == LEXER_ENV)
		return (TOK_ENV_VAR);
	else if (state == LEXER_SQUOTE || state == LEXER_DQUOTE)
		return (TOK_QUOTED);
	else
		return (TOK_WORD);
}

const char	*token_type_to_string(t_toktype type)
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
		ft_printf("Token: %s | type %s\n",
			(char *)tokens->content, token_type_to_string(tokens->type));
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

t_lexstate	add_token(t_mshell *shell, t_lexer *l, t_toktype type)
{
	t_token	*new;
	t_token	*last;

	if (!l->buffer || !*l->buffer)
		return (l->state);
	new = ft_malloc_s(shell, sizeof(t_token), MEM_TEMP);
	if (!new)
		return (LEXER_ERROR);
	new->content = ft_strdup_s(shell, l->buffer, MEM_TEMP);
	if (!new->content)
		return (LEXER_ERROR);
	new->type = type;
	new->next = NULL;
	if (!l->tokens)
		l->tokens = new;
	else
	{
		last = l->tokens;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	l->buffer = NULL;
	return (l->state);
}
