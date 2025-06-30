/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:44:34 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 13:56:04 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd()
{
	char	*result;

	result = getcwd(NULL, 0);
	if (!result)
	{
		ft_putstr_fd("getcwd failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(result, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(result);
	return (EXIT_SUCCESS);
}
