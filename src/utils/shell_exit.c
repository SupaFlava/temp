/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:43:16 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 14:34:57 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_shell(t_mshell *shell, int exit_code, bool long_clean)
{
	if (shell->line)
		free(shell->line);
	shell->line = NULL;
	ft_free(shell, MEM_TEMP);
	if (long_clean)
		ft_free(shell, MEM_LONG);
	rl_clear_history();
	ft_putstr_fd("exit\n",STDOUT_FILENO);
	exit(exit_code);
}