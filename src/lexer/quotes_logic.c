/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes_logic.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/02 15:20:07 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/02 16:54:05 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_new_quote_group(t_lexer *l)
{
	l->current_quote_id++;
	l->in_dquote = true;
}

void	end_quote_group(t_lexer *l)
{
	l->in_dquote = false;
}

int	get_quote_id(t_lexer *l)
{
	if (l->in_dquote)
		return (l->current_quote_id);
	return (-1);
}
