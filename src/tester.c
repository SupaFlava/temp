/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:42:35 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/15 15:20:01 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int run_builtin(t_command *cmd, t_mshell *shell)
{
    if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
        return builtin_cd(shell, cmd->args);
    else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
        return builtin_pwd(shell);
	else if (ft_strncmp(cmd->args[0], "echo",ft_strlen(cmd->args[0])) == 0)
		return(builtin_echo(shell, cmd->args));
	else if (ft_strncmp(cmd->args[0], "env",ft_strlen(cmd->args[0])) == 0)
		return(builtin_env(shell, cmd->args));
	else
		return (0);
}
