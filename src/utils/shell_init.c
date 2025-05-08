/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 11:06:16 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/08 12:50:27 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_init(t_mshell *shell)
{
	ft_bzero(shell, sizeof(t_mshell));
	shell->exit_status = 0;
	return (EXIT_SUCCESS);
}
