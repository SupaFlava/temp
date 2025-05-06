/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:25:12 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/06 11:19:40 by rmhazres         ###   ########.fr       */
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

typedef struct s_mihell
{
    t_env *env_list;
	char  *line;
	int		exit_status;
} t_mshell;
# endif