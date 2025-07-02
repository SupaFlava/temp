/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:44:34 by rmhazres          #+#    #+#             */
/*   Updated: 2025/07/02 14:29:02 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*result;

	result = getcwd(NULL, 0);
	if (!result)
	{
		perror("minishell: pwd");
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(result, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(result);
	return (EXIT_SUCCESS);
}
