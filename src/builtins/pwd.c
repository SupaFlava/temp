/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:44:34 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/06 15:54:57 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd()
{
	char *buffer;
	char *result;
	
	buffer = malloc(512);
	result = getcwd(buffer, 512);
	ft_printf("%s\n",result);
	return (0);
}