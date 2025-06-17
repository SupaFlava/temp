/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:23:04 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/17 14:39:53 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_access(char *path)
{
	if (access(path, F_OK)< 0)
		ft_printf("bash: %s No such file or directory\n", path);
	else if (errno == EACCES)
		ft_printf("bash: %s Permission denied\n",path);
	else
		ft_printf("command: %s not found \n",path);
}
static int	run_direct_path_exec(t_command *cmd, char **envp)
{
	if (!is_executable(cmd->args[0]))
	{
		check_access(cmd->args[0]);
		return (1);
	}
	execve(cmd->args[0], cmd->args, envp);
	ft_printf("bash: %s: %s\n", cmd->args[0], strerror(errno));
	return (1);
}

static int	run_search_exec(t_command *cmd, t_env *envl, char **envp)
{
	char *path;

	path = find_in_path(cmd->args[0], envl);
	if (!path)
	{
		ft_printf("bash: %s: command not found\n", cmd->args[0]);
		return (1);
	}
	for (int i = 0; envp[i]; i++)
    printf("envp[%d]: %s\n", i, envp[i]);
	execve(path, cmd->args, envp);
	ft_printf("bash: %s: %s\n", path, strerror(errno));
	free(path);
	return (1);
}

int check_exec(t_command *cmd, t_mshell *shell)
{
	char **envp;
	int ret;

	if(!cmd || !cmd->args || !cmd->args[0])
		return (1);
	envp = env_to_envp(shell);
	if (!envp)
		return(-1);
	if (ft_strchr(cmd->args[0], '/') != NULL)
		ret = run_direct_path_exec(cmd, envp);
	else
		ret = run_search_exec(cmd, shell->env_list, envp);
	free_arr(envp);
	return (ret);
}
