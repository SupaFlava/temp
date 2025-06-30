/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:45:29 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 13:41:30 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(t_mshell *shell, char *path)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		old_path = ft_strdup("");
	if (chdir(path) == 0)
	{
		set_env(shell, "OLDPWD", old_path);
		free(old_path);
		new_path = getcwd(NULL, 0);
		if (new_path)
		{
			set_env(shell, "PWD", new_path);
			free(new_path);
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		free(old_path);
		return (EXIT_FAILURE);
	}
}

int	builtin_cd(t_mshell *shell, char **args)
{
	int		argc;
	t_env	*path;

	argc = count_args(args);
	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argc == 1)
	{
		path = get_env(shell->env_list, "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		return (change_dir(shell, path->value));
	}
	else
		return (change_dir(shell, args[1]));
}
