/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:39:22 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/16 10:49:51 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

int     init_env(t_mshell *shell,char **envp);
void    env_add_back(t_env **shell, t_env *new_node);
void	env_print(t_mshell *shell);

#endif