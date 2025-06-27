/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/26 18:15:06 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/25 20:31:52 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_input(t_command *cmd)
{
	t_redir	*node;
	int		fd;

	node = cmd->infile;
	while (node)
	{
		fd = open(node->file, O_RDONLY);
		if (fd < 0)
		{
			perror(node->file);
			return (-1);
		}
		if (!node->next)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (-1);
			}
		}
		close(fd);
		node = node->next;
	}
	return (0);
}

int	redir_out(t_command *cmd)
{
	t_redir	*node;
	int		fd;

	node = cmd->outfile;
	if (!node)
		return (0);
	while (node)
	{
		if (node->append)
			fd = open(node->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(node->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(node->file);
			return (-1);
		}
		if (!node->next)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (-1);
			}
		}
		close(fd);
		node = node->next;
	}
	return (0);
}

int	handle_redir(t_command *cmd)
{
	if (cmd->infile)
	{
		if (redir_input(cmd) < 0)
			return (-1);
	}
	if (cmd->outfile)
	{
		if (redir_out(cmd) < 0)
			return (-1);
	}
	return (0);
}
