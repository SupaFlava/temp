/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:39:22 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 16:21:31 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

int		init_env(t_mshell *shell, char **envp);
void	env_add_back(t_env **shell, t_env *new_node);
int		env_add(t_mshell *shell, char *key, char *value);

void	env_print(t_mshell *shell);
t_env	*get_env(t_env *env, char *key);
int		set_env(t_mshell *shell, char *key, char *value);
int		delete_env(t_env **list, t_env *node);
int		count_env(t_env *env);

#endif