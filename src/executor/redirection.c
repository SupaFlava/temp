/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:15:06 by rmhazres          #+#    #+#             */
/*   Updated: 2025/07/07 14:09:17 by rmhazres         ###   ########.fr       */
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
		if (!node->file)
			return (ft_putstr_fd("No such file or dir\n", STDERR_FILENO), -1);
		fd = open(node->file, O_RDONLY);
		if (fd < 0)
			return (perror(node->file), -1);
		if (!node->next)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				safe_close(&fd);
				return (-1);
			}
		}
		safe_close(&fd);
		node = node->next;
	}
	return (0);
}

int	redir_out(t_command *cmd)
{
	t_redir	*node;
	int		fd;

	node = cmd->outfile;
	while (node)
	{
		if (!node->file)
			return (ft_putstr_fd("No such file or dir\n", STDERR_FILENO), -1);
		if (node->append)
			fd = open(node->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(node->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(node->file), -1);
		if (!node->next)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (perror("dup2"), safe_close(&fd), -1);
		}
		safe_close(&fd);
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
