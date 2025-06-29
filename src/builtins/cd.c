/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 15:45:29 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/29 19:57:56 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(t_mshell *shell, char *path)
{
	char	*old_path;
	char	*buffer;

	buffer = ft_malloc_s(shell, 512, MEM_TEMP);
	old_path = getcwd(buffer, 512);
	if (chdir(path) == 0)
	{
		set_env(shell->env_list, "OLDPWD", old_path);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
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
