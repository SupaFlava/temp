/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:39:22 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/21 15:34:17 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

int     init_env(t_mshell *shell,char **envp);
void    env_add_back(t_env **shell, t_env *new_node);
void	env_print(t_mshell *shell);
t_env 	*get_env(t_env *env , char *key);
int		set_env(t_env *env, char *key, char *value);
int		dl_env(t_env *list,char *key);

#endif