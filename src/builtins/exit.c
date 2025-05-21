/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:38:28 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/21 13:16:04 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long builtin_exit(t_mshell *shell, char **args)
{
	long status;

	status = 0;
	if (count_args(args) > 2)
	{
			ft_printf("exit\n");
			ft_printf("bash: exit: too many arguments\n");
			return (0);
	} else if (count_args(args) == 2)
	{
		if (!is_numeric(args[1]))
		{
			ft_printf("exit\n");
			ft_printf("exit: %s: numeric argument required\n", args[1]);
			status = 255;
		}
		else
			status = ft_atoi(args[1]);	
	}
	printf("exit\n");
	ft_free(shell,MEM_TEMP);
	ft_free(shell,MEM_LONG);
	exit (status);
}
