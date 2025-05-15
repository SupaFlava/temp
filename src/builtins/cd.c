/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:45:29 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/15 15:24:45 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_args(char **args)
{
	int i;
	
	i = 0;
	while (args[i])
		i++;
	return i;
}

int	builtin_cd(t_mshell shell,char **args)
{
	(void)shell;
	int argc;

	argc = count_args(args);
	ft_printf("cound is %s\n",argc);
	return (0);
}