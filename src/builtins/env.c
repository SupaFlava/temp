/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:16:01 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/19 21:41:51 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_mshell *shell, char **args)
{
	int	argc;

	argc = count_args(args);
	ft_printf("argc is %i\n", argc);
	if (argc == 1)
	{
		env_print(shell);
		return (EXIT_SUCCESS);
	}
	ft_printf("Should not have args\n");
	return (EXIT_FAILURE);
}
