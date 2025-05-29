/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:20:51 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/29 18:36:30 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void wait_for_pid(int amount , int pids[])
{
	while (amount >= 0)
	{
		waitpid(pids[amount], NULL, 0);
		amount--;
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

static pid_t run_child(t_command *cmd, int prev_fd, int fds[])
{
	pid_t pid;
	
	pid = fork();
	
	if (pid == -1)
		return (perror("Fork"), -1);
	if (pid == 0)
	{
	if(prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			if (cmd->next)
				dup2(fds[1], STDOUT_FILENO);
			close_fds(prev_fd, fds[0], fds[1]);
			handle_redir(cmd);
		//	check_exec(cmd);
			exit(0);	
	}
	return (pid);
}

int execute_cmd(t_mshell *shell)
{
	t_command *cmd;
	t_exec_ctx *ctx = NULL;
	
	cmd = &shell->cmds;
	init_context(ctx);
	int i;
	int pid;
	
	i = 0;
	while(cmd)
	{
		if(prep_pipe(cmd, ctx->fds) < 0)
			return (1);
		pid = run_child(cmd ,ctx->prev_fd, ctx->fds);
		if(pid < 0)
			return 1;
		ctx->child_pids[i++] = pid;
		close_parent_fds(cmd,&ctx->prev_fd, ctx->fds);
		cmd = cmd->next;
	}
	wait_for_pid(i , ctx->child_pids);
	return (0);
}
