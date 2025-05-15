/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:39:22 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/09 19:28:42 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

int		init_env(t_mshell *shell, char **envp);
void	env_add_back(t_env **shell, t_env *new_node);

#endif