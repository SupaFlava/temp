/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:38:28 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 11:01:29 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_mshell *shell, char **args)
{
	long	status;

	status = 0;
	if (count_args(args) > 2)
	{
		ft_printf("exit\n");
		ft_printf("minishell: exit: too many arguments\n");
		return ;
	}
	else if (count_args(args) == 2)
	{
		if (!is_numeric(args[1]))
		{
			print_err("exit\nminishell", args[1], "numeric argument required");
			status = 2;
		}
		else
		{
			status = ft_atoi(args[1]) % 255;
			ft_printf("exit\n");
		}
	}
	ft_printf("exit\n");
	return(exit_shell(shell,(int)(unsigned)(status),true));
}
