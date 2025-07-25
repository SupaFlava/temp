/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:06:16 by rmhazres          #+#    #+#             */
/*   Updated: 2025/07/08 10:29:13 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_init(t_mshell *shell)
{
	ft_bzero(shell, sizeof(t_mshell));
	shell->long_allocs = NULL;
	shell->temp_allocs = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->exit_status = 0;
	shell->should_exit = false;
}

void	init_context(t_exec_ctx *ctx)
{
	int	i;

	i = 0;
	ctx->prev_fd = -1;
	ctx->child_count = 0;
	ctx->last_exit_status = 0;
	ctx->fds[0] = -1;
	ctx->fds[1] = -1;
	while (i < MAX_CHILDREN)
	{
		ctx->child_pids[i] = 0;
		i++;
	}
}
