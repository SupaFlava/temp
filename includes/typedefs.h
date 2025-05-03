/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:25:12 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/03 16:32:05 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env *next;
} t_env;

typedef struct s_mshell
{
    t_env *env_list;
} t_mshell;
# endif