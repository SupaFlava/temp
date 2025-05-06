/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:25:12 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/06 15:47:08 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H


typedef struct s_mem
{
	void	*ptr;
	struct s_mem *next;
} t_mem;

typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env *next;
} t_env;

typedef struct s_command
{
	char	**args;
	char	*infile;
	char	*outfile;
	int 	append;
	struct s_command *next;
} t_command;


typedef struct s_mshell
{
	t_list *mem_list;
    t_env *env_list;
	char  *line;
	int		exit_status;
	t_command cmds;
} t_mshell;
# endif