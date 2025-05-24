/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:20:51 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/24 14:48:35 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*t_command cmd3 = {
    .args = (char *[]){"hello.txt", NULL},
    .infile = NULL,
    .outfile = NULL,
    .append = 0,
    .next = NULL
};

t_command cmd2 = {
    .args = (char *[]){"echo", NULL},
    .infile = NULL,
    .outfile = NULL,
    .append = 0,
    .next = &cmd3
};

t_command cmd1 = {
    .args = (char *[]){"ls", NULL},
    .infile = NULL,
    .outfile = NULL,
    .append = 0,
    .next = &cmd2
};*/

int excute_cmd(t_mshell *shell)
{
	t_command *cmd;
	int fds[2];
	int prev_fd;
	int pid;

	cmd = &shell->cmds;
	
	prev_fd = -1;
	while(cmd)
	{
		if (cmd->next != NULL)
		{
				if (pipe(fds)  == -1)
					return (printf("error"), 1);
		}
		pid = fork();
		if (pid == 0) // this is a child;
		{
			
		}	
	}
}