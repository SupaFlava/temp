/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 19:08:53 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/02 13:33:10 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexstate	handle_char(t_mshell *shell, t_lexer *l, char c)
{
	if (l->state == LEXER_DEFAULT)
		return (default_state(shell, l, c));
	else if (l->state == LEXER_ASSIGN)
		return (assign_state(shell, l, c));
	else if (l->state == LEXER_SQUOTE)
		return (s_quote_state(shell, l, c));
	else if (l->state == LEXER_DQUOTE)
		return (d_quote_state(shell, l, c));
	else if (l->state == LEXER_ENV || l->state == LEXER_QUOTED_ENV)
		return (env_state(shell, l, c));
	else if (l->state == LEXER_REDIR_IN || l->state == LEXER_REDIR_OUT)
		return (redir_state(shell, l, c));
	return (LEXER_ERROR);
}

void	init_lexer(t_mshell *shell, t_lexer *l)
{
	ft_bzero(l, sizeof(t_lexer));
	l->input = shell->line;
	l->index = 0;
	l->state = LEXER_DEFAULT;
	l->buffer = NULL;
	l->tokens = NULL;
}

int	process_line_loop(t_mshell *shell, t_lexer *l)
{
	char	c;

	c = l->input[l->index];
	while (l->input[l->index])
	{
		c = l->input[l->index];
		l->state = handle_char(shell, l, c);
		if (l->state == LEXER_ERROR)
			return (0);
		l->index++;
	}
	if (!validate_tokens(l))
	{
		print_err("minishell", "syntax error: unexpected end after", "'|'");
		return (0);
	}
	return (1);
}

t_token	*lexer(t_mshell *shell)
{
	t_lexer	*l;

	if (!shell->line || *(shell->line) == '\0')
		return (NULL);
	l = ft_malloc_s(shell, sizeof(t_lexer), MEM_TEMP);
	if (!l)
		return (NULL);
	init_lexer(shell, l);
	if (!process_line_loop(shell, l))
		return (NULL);
	if (!finalize_tokens(shell, l))
		return (NULL);
	return (l->tokens);
}
