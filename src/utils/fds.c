/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:40:06 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/29 18:42:24 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_fds(int fd1,int fd2, int fd3)
{
	if (fd1 >= 0 )
		close(fd1);
	if (fd2 >= 0 )
		close(fd2);
	if (fd3 >= 0 )
		close(fd3);
}

void    close_parent_fds(t_command *cmd, int *prev_fd, int fds[2])
{
    if (*prev_fd != -1)
        close(*prev_fd);
    if (cmd->next)
    {
        close(fds[1]);
        *prev_fd = fds[0];
    }
}
