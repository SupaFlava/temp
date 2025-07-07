/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 16:38:28 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/07/07 16:50:19 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_digits_only(const char *str)
{
	int i = 0;

	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_signed_exit_status(t_mshell *shell, char **args)
{
	if (count_args(args) > 2)
	{
		if (ft_strcmp(args[1], "+") == 0 || ft_strcmp(args[1], "-") == 0)
		{
			if (!is_digits_only(args[2]))
			{
				print_err("minishell: exit", args[2], "numeric argument required");
				exit_shell(shell, 2, true);
			}

			if (ft_strcmp(args[1], "-") == 0)
				return (-ft_atoi(args[2]));
			else
				return (ft_atoi(args[2]));
		}
	}
	return (0);
}

int	builtin_exit(t_mshell *shell, char **args)
{
	int	status;

	status = 0;

	status = parse_signed_exit_status(shell, args);
	if (count_args(args) > 2 && is_valid_numeric(args[1]))
	{
		print_err("minishell", args[0], "too many arguments");
		return (EXIT_FAILURE);
	}
	else if (count_args(args) == 2)
	{
		if (!is_valid_numeric(args[1]))
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
