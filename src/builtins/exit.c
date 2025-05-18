/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:38:28 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/18 13:27:31 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_exit(t_mshell *shell, char **args)
{
	(void)shell;
	int status;

	status = 0;
	if (count_args(args) > 2)
	{
			ft_printf("exit\n");
			ft_printf("bash: exit: too many arguments\n");
			status = 1;
	} else if (count_args(args) == 2)
	{
		if (!is_numeric(args[1]))
		{
			ft_printf("exit\n");
			ft_printf("exit: %s: numeric argument required", args[1]);
			status = 255;
		}
		else
			status = args[1];	
		
		
	}
	return (0);
	
}