/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:20:51 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/05 15:41:32 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void wait_for_pid(int amount, int pids[], t_mshell *shell)
{
	int i;
	int status;

	i = 0;
	status = -1;
	shell->exit_status = 0;
	while (i < amount)
	{
		waitpid(pids[i], &status, 0);
		if(i == amount -1)
		{
			if(WEXITSTATUS(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

static int	prep_pipe(t_command *cmd, int *fds)
{
	if(cmd->next)
	{
		if (pipe(fds) == -1)
			return (printf("error"), 1);
	}
	return (0);
}

static pid_t run_child(t_command *cmd,t_exec_ctx ctx ,t_mshell *shell)
{
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
		return (perror("Fork"), -1);
	if (pid == 0)
	{
	if(ctx.prev_fd != -1)
				dup2(ctx.prev_fd, STDIN_FILENO);
			if (cmd->next)
				dup2(ctx.fds[1], STDOUT_FILENO);
			close_fds(ctx.prev_fd, ctx.fds[0], ctx.fds[1]);
			handle_redir(cmd);
			if(is_builtin(cmd))
				exit(run_builtin(cmd, shell));
			else
			{
				check_exec(cmd, shell);
			}
			exit(0);
	}
	return (pid);
}

int execute_cmd(t_mshell *shell)
{
	t_command *cmd;
	t_exec_ctx ctx;
	int pid;
	
	cmd = shell->commands;
	init_context(&ctx);
	
	if(!cmd->args[0] || !cmd->args)
		return (0);
	while(cmd)
	{
		if(is_builtin(cmd) && !cmd->next && ctx.prev_fd == -1)
			return (run_builtin(cmd, shell));
		if(prep_pipe(cmd, ctx.fds) < 0)
			return (1);
		pid = run_child(cmd ,ctx,shell);
		if(pid < 0)
			return (1);
		ctx.child_pids[ctx.child_count++] = pid;
		close_parent_fds(cmd, &ctx.prev_fd, ctx.fds);
		cmd = cmd->next;
	}
	wait_for_pid(ctx.child_count, ctx.child_pids, shell);
	return (0);
}
