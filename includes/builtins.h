/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:34:16 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/16 11:45:19 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	builtin_pwd(t_mshell *shell);
int	builtin_cd(t_mshell *shell, char **args);
int	builtin_echo(t_mshell *shell ,char **args);
int	builtin_env(t_mshell *shell, char **args);

#endif