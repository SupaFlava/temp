/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:16:01 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/29 21:57:30 by jbaetsen      ########   odam.nl         */
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
	print_err("env", args[1], "No such file or directory");
	return (CMD_NOT_FOUND);
}
