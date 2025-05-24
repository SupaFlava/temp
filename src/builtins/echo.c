/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:07:34 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/24 11:45:08 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// builtin_echo(shell, (char *[]){"echo", "-n", "hello", "world", NULL});

int	builtin_echo(t_mshell *shell ,char **args)
{
	(void)shell;
	int i;
	int flag;

	flag = 0;
	i = 2;
	if (ft_strlen(args[1]) == 2 && ft_strncmp(args[1], "-n" ,2) == 0)
		flag =1;
	while (args[i] != NULL)
	{
		ft_printf("%s",args[i]);
		i++;
		if (args[i] == NULL && flag == 0)
			ft_printf("\n");
		else if (args[i] == NULL && flag == 0)
			break;
		else if (args[i] != NULL)
			ft_printf(" ");
	}
	return (0);
}
