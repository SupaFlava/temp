/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:20:51 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/26 20:01:47 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_cmd(t_mshell *shell)
{
	t_command *cmd;
	int fds[2];
	int prev_fd;
	int pid;
	int child_pids[100];
	cmd = &shell->cmds;
	int i;
	
	i = 0;
	prev_fd = -1;
	while(cmd)
	{
		if (cmd->next != NULL)
				if (pipe(fds)  == -1)
					return (printf("error"), 1);
		pid = fork();
		if (pid == 0) // this is a child;
		{
			if(prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->next)
			{
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
				close(fds[0]);
			}
			handle_redir(cmd);
			// handle infile outfile redirection
			// exec or builtin
			child_pids[i++] = pid;
			exit(0);
		}
		else
		{	// parent
			for (int j = 0; j < i; j++)
				waitpid(child_pids[j], NULL, 0);
			if (prev_fd != -1)
			{
				printf("from parent \n");
				close(prev_fd);	
			}
			if (cmd->next)
			{
				printf("parent has next cmd\n");
				close(fds[1]);
				prev_fd = fds[0];
			}
		}
		cmd = cmd->next;
	}
	return (0);
}
