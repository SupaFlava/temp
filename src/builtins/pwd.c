/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:44:34 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/15 12:12:35 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_mshell *shell)
{
	char *buffer;
	char *result;
	
	buffer = ft_malloc_s(shell ,512, MEM_TEMP);
	if (!buffer)
		return (EXIT_FAILURE);
	result = getcwd(buffer, 512);
	if (!result)
		{
			ft_printf("getcwd failed\n");
			return (EXIT_FAILURE);
		}
	ft_printf("%s\n",result);
	return (EXIT_SUCCESS);
}
