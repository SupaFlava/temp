/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:34:16 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/18 11:18:36 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		builtin_pwd(t_mshell *shell);
int		builtin_cd(t_mshell *shell, char **args);
int		builtin_echo(t_mshell *shell, char **args);
int		builtin_env(t_mshell *shell, char **args);
long	builtin_exit(t_mshell *shell, char **args);
int		builtin_unset(t_mshell *shell, char **args);
int		is_builtin(t_command *cmd);
int		run_builtin(t_command *cmd, t_mshell *shell);
int		builtin_export(t_mshell *shell, char **args);

#endif