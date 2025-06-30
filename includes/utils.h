/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:22:37 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 11:01:59 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// includes
# include "libft.h"
# include "typedefs.h"

// function prototypes
// shell_init.c
void	shell_init(t_mshell *shell);
void	init_context(t_exec_ctx *ctx);

// memory
void	free_env(t_env *node);
void	ft_free(t_mshell *shell, t_mem_t type);
void	*ft_malloc_s(t_mshell *shell, size_t size, t_mem_t type);
void	free_arr(char **arr);

// str_utils.c
char	*ft_strdup_s(t_mshell *shell, const char *src, t_mem_t type);
char	*ft_strndup_s(t_mshell *shell, const char *str, size_t n, t_mem_t type);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_substr_s(t_mshell *shell, char const *s, unsigned b, size_t len);
char	*ft_itoa_s(t_mshell *shell, int n, t_mem_t type);
char	*ft_strjoin_s(char const *s1, char const *s2, t_mshell *sh, t_mem_t t);

void exit_shell(t_mshell *shell, int exit_code, bool long_clean);


// fds.c
void	close_fds(int fd1, int fd2, int fd3);
void	close_parent_fds(t_command *cmd, int *prev_fd, int fds[2]);

// args_utils.c
int		count_args(char **args);
int		is_numeric(char *arg);

// error.c
void	print_err(char *prefix, char *arg, char *msg);

#endif