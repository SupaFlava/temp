/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:15:06 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/06 21:52:19 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redir_input(t_command *cmd)
{
    int fd;

    if (!cmd->infile)
        return (0);
    fd = open(cmd->infile, O_RDONLY);
    if (fd < 0 )
        return (-1);
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

int redir_out(t_command *cmd)
{
    int fd;
    
    if(cmd->append)
    {
       fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
       if (fd < 0)
            return (-1);
       dup2(fd, STDOUT_FILENO);
       close(fd);
    }
    else
    {
       fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
       if (fd < 0)
            return (-1);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return (0);
}

int handle_redir(t_command *cmd)
{
    if (redir_input(cmd) < 0)
        return (-1);
    if (redir_out(cmd) < 0)
        return (-1);
    return (0);
}
