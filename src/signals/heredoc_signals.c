/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_signals.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/15 15:39:53 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/27 17:35:57 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_heredoc(int sig)
{
	//(void)sig;
	g_signal = sig;
	write(1, "\n", 1);
	exit(130);
}
