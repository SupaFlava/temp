/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:06:31 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/18 13:20:23 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **args)
{
	int i;

	i = 0;
	while(args[i])
	{
		i++;
	}
	return (i);
}

int is_numeric(char *arg)
{
	long long i;

	i = 0;
	while(arg[i])
	{
		if(!is_digit(arg[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
