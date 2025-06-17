/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:20:51 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/15 14:17:06 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void restore_stdio(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

static int execute_single_builtin(t_command *cmd, t_mshell *shell)
{
	int saved_stdin;
	int saved_stdout;
	int ret;
	
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
 	if (handle_redir(cmd) < 0)
	{
		restore_stdio(saved_stdin, saved_stdout);
		return (1);
	}
	ret = run_builtin(cmd, shell);
	restore_stdio(saved_stdin, saved_stdout);
	if (cmd->is_heredoc && cmd->heredoc_fd != -1)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	return (ret);
}

static int is_single_builtin(t_command *cmd, t_exec_ctx *ctx)
{
	return(is_builtin(cmd) && !cmd->next && ctx->prev_fd == -1);	
}
int	execute_cmd(t_mshell *shell)
{
	t_exec_ctx ctx;
	t_command *cmd;
	
	init_context(&ctx);
	cmd = shell->commands;
	if(!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_single_builtin(cmd, &ctx))
		return (execute_single_builtin(cmd, shell));
	return (execute_pipeline(cmd, shell, &ctx));
}
