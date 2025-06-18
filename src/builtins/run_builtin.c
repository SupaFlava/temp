/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:44:20 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/18 11:19:43 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_command *cmd)
{
	if(!cmd)
		return (0);
    if (ft_strcmp(cmd->args[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        return (1);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return(1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return(1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return(1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return(1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return(1);
	else
		return (0);
}
int run_builtin(t_command *cmd, t_mshell *shell)
{
    if (ft_strcmp(cmd->args[0], "cd") == 0)
        return builtin_cd(shell, cmd->args);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        return builtin_pwd(shell);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return(builtin_echo(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return(builtin_env(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return(builtin_exit(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return(builtin_unset(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return(builtin_export(shell, cmd->args));
	else
		return (0);
}
