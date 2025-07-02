/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 16:38:28 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/07/02 17:06:10 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_mshell *shell, char **args)
{
	int	status;

	status = 0;
	if (count_args(args) > 2)
	{
		print_err("minishell", args[0], "too many arguments");
		return (EXIT_FAILURE);
	}
	else if (count_args(args) == 2)
	{
		if (!is_numeric(args[1]))
		{
			print_err("minishell: exit", args[1], "numeric argument required");
			status = 2;
			exit_shell(shell, status, true);
		}
		else
			status = ft_atoi(args[1]) & 0xFF;
	}
	exit_shell(shell, (int)(unsigned)(status), true);
	return (status);
}
