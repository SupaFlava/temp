/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:09:41 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/14 11:39:47 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int fork_heredoc(t_command *cmd , t_mshell *shell)
{
    int pid;
    int status;
    const char *temp_file;

    temp_file = ".heredoc_tmp";
    pid = fork();
    if (pid == -1)
    {
        perror("heredoc fork fail");
        return (1);
    }
    if (pid == 0)
    {
        exit(1);
    }
    waitpid(pid, &status, 0);
    if (WIFCONTINUED(status) && WEXITSTATUS(status) == 0)
    {
        cmd->infile = ft_strdup_s(shell ,temp_file,MEM_TEMP);
        cmd->heredoc_fd = -2;
        return (0);
    }
    return (1);
}

void    handle_heredoc(t_command *cmd, t_mshell *shell)
{
    int fds[2];
    char *line;
    int ret;

    (void)shell;
    ret = 0;
    if(pipe(fds) == -1)
    {
        perror("pipe");
        cmd->heredoc_fd = -1;
        return;
    }
    while (ret == 0)
    {
        line = readline("heredoc >");
        if (!line)
        {
            if (ret == 0)
            {
                // Write warning to stderr
                write(2, "warning: here-document delimited by end-of-file (wanted `", 55);
                write(2, cmd->delimiter, ft_strlen(cmd->delimiter));
                write(2, "')\n", 3);
            }
            break;
        }
        if (ft_strcmp(line, cmd->delimiter) == 0)
        {
            free(line);
            break;
        }
        if (write(fds[1], line, ft_strlen(line)) < 0 || write(fds[1], "\n", 1) < 0)
        {
            perror("write");
            free(line);
            ret = -1;
            break;
        }
        free(line);
    }
    close(fds[1]);
    if (ret == -1)
    {
        close(fds[0]);
        cmd->heredoc_fd = -1;
    }
    else
        cmd->heredoc_fd = fds[0];
}
