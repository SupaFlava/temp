/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:23:04 by rmhazres          #+#    #+#             */
/*   Updated: 2025/07/08 10:05:01 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access(char *path)
{
	if (access(path, F_OK) < 0)
	{
		print_err("minishell: ", path, "No such file or directory");
		return (127);
	}
	else if (access(path, X_OK) < 0)
	{
		print_err("minishell: ", path, "Permission denied");
		return (126);
	}
	else
	{
		print_err("minishell: ", path, "Command failed to execute");
		return (126);
	}
}

static int	run_direct_path_exec(t_mshell *shell, t_command *cmd, char **envp)
{
	struct stat	st;

	if (stat(cmd->args[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_err("minishell", cmd->args[0], "Is a directory");
		return (126);
	}
	if (!is_executable(cmd->args[0]))
	{
		shell->exit_status = check_access(cmd->args[0]);
		exit (shell->exit_status);
	}
	execve(cmd->args[0], cmd->args, envp);
	print_err("minishell", cmd->args[0], strerror(errno));
	exit (EXIT_FAILURE);
}

static int	run_search_exec(t_command *cmd, t_env *envl, char **envp)
{
	char			*path;
	struct stat		st;

	path = find_in_path(cmd->args[0], envl);
	if (!path)
	{
		print_err("minishell", cmd->args[0], "command not found");
		exit (CMD_NOT_FOUND);
	}
	if (stat(cmd->args[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_err("minishell", cmd->args[0], "Is a directory");
		exit (126);
	}
	execve(path, cmd->args, envp);
	print_err("minishell", path, strerror(errno));
	free(path);
	exit (EXIT_FAILURE);
}

int	check_exec(t_command *cmd, t_mshell *shell)
{
	char	**envp;
	int		ret;

	if (!cmd || !cmd->args[0] || ft_strlen(cmd->args[0]) == 0)
		return (0);
	envp = env_to_envp(shell);
	if (!envp)
		return (-1);
	if (ft_strchr(cmd->args[0], '/') != NULL)
		ret = run_direct_path_exec(shell, cmd, envp);
	else
		ret = run_search_exec(cmd, shell->env_list, envp);
	shell->exit_status = ret;
	free_arr(envp);
	return (ret);
}
