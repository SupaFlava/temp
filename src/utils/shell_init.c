/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:06:16 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/08 17:16:44 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_init(t_mshell *shell)
{
	ft_bzero(shell, sizeof(t_mshell));
	shell->long_allocs = NULL;
	shell->temp_allocs = NULL;
	shell->exit_status = 0;
	return (EXIT_SUCCESS);
}
