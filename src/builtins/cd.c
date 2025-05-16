/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:45:29 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/16 13:52:44 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int change_dir(t_mshell *shell, char *path)
{
	char *old_path;
	char *buffer;

	
	buffer = ft_malloc_s(shell ,512, MEM_TEMP);
	old_path = getcwd(buffer, 512);
	if (chdir(path) == 0)
	{
		set_env(shell->env_list ,"OLDPWD",old_path);
	//	free(old_path);
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int	builtin_cd(t_mshell *shell, char **args)
{
	(void)shell;
	int argc;
	char *path;

	argc = count_args(args);
	env_print(shell);
	if (argc > 2)
	{
		ft_printf("cd: too many arguments");
		return (EXIT_FAILURE);
	}
	if (argc == 1)
	{

		path = get_env(shell->env_list,"HOME");
		if (path == NULL)
		{
			ft_printf("cant find home env\n");
			return (EXIT_FAILURE);
		}
		change_dir(shell, path);
		ft_printf("after cd after cd ------------------\n");
		env_print(shell);
	}
	//else if(argc)
	return (0);
}
