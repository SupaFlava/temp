/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:16:01 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/29 20:03:33 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_mshell *shell, char **args)
{
	int		argc;

	argc = count_args(args);
	if (argc == 1)
	{
		env_print(shell);
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd("env: '", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
	return (CMD_NOT_FOUND);
}
