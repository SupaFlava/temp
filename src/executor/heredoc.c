/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/10 13:09:41 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/19 22:11:45 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prep_heredoc(t_mshell *shell)
{
	t_command	*cmd;
	int			i;

	cmd = shell->commands;
	i = 0;
	while (cmd)
	{
		if (cmd->is_heredoc)
		{
			if (fork_heredoc(cmd, shell, i) != 0)
				return (1);
		}
		cmd = cmd->next;
		i++;
	}
	return (0);
}

static char	*generate_heredoc_file(int index, t_mshell *shell)
{
	char	*base;
	char	*suffix;
	char	*full;

	base = ft_strdup_s(shell, ".heredoc_temp", MEM_TEMP);
	if (!base)
		return (NULL);
	suffix = ft_itoa_s(shell, index, MEM_TEMP);
	if (!suffix)
		return (NULL);
	full = ft_strjoin_s(base, suffix, shell, MEM_TEMP);
	if (!full)
		return (NULL);
	return (full);
}

int	fork_heredoc(t_command *cmd, t_mshell *shell, int index)
{
	int		pid;
	int		status;
	char	*filename;

	filename = generate_heredoc_file(index, shell);
	if (!filename)
		return (perror("genereating filename"), 1);
	cmd->heredoc_temp = filename;
	pid = fork();
	if (pid == -1)
		return (perror("heredoc fork fail"), 1);
	if (pid == 0)
		exit(handle_heredoc(cmd, filename));
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		add_infile(shell, cmd, cmd->heredoc_temp);
		cmd->heredoc_fd = -2;
		return (0);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		shell->exit_status = 130;
	return (1);
}

static int	check_line(char *line, t_command *cmd)
{
	if (!line)
	{
		ft_putstr_fd("warning: heredoc delimited by EOF (wanted `", 2);
		ft_putstr_fd(cmd->delimiter, 2);
		ft_putstr_fd("`)\n", 2);
		return (0);
	}
	return (1);
}

int	handle_heredoc(t_command *cmd, const char *filename)
{
	int		fd;
	char	*line;

	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("heredoc open fails"), 1);
	unlink(filename);
	while (1)
	{
		line = readline("Heredoc > ");
		if (!check_line(line, cmd))
			break ;
		if (ft_strcmp(line, cmd->delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	return (0);
}
