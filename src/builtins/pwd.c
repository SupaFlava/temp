/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:44:34 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/08 15:41:51 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_mshell *shell)
{
	char *buffer;
	char *result;
	
	buffer = ft_malloc_s(shell ,512, MEM_TEMP);
	result = getcwd(buffer, 512);
	ft_printf("%s\n",result);
	return (0);
}