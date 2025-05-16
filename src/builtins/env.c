/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 12:16:01 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/16 14:36:57 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_mshell *shell , char **args)
{

	if (args[2] == NULL)
	{
		env_print(shell);
		return (EXIT_SUCCESS);
	}
	ft_printf("Should not have args\n");
	return(EXIT_FAILURE);
}
