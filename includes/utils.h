/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 11:22:37 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/27 23:00:03 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// includes
# include "libft.h"
# include "typedefs.h"

// function prototypes
// shell_init.c
int			shell_init(t_mshell *shell);
void		*ft_malloc_s(t_mshell *shell, size_t size, t_mem_t type);
void		ft_free(t_mshell *shell, t_mem_t type);
int			shell_init(t_mshell *shell);

// str_utils.c
char		*ft_strdup_s(t_mshell *shell, const char *src, t_mem_t type);
char		*ft_strndup(t_mshell *shell, const char *str, size_t n);
char		*ft_strcpy(char *dst, const char *src);
int			ft_strcmp(const char *str1, const char *str2);

// list_utils.c


// args_utils.c
int	count_args(char **args);

// tester.c
void	print_commands(t_command *cmd_list);

#endif