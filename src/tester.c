/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:42:35 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/06 15:55:50 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int run_builtin(t_command *cmd, t_mshell *shell)
{
    if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
        return builtin_cd(cmd, shell);
    else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
        return builtin_pwd();
	else
		return (0);
}
