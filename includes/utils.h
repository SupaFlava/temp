/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 11:22:37 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/19 17:02:46 by jbaetsen      ########   odam.nl         */
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
void		print_tokens(t_token *tokens);
void		free_tokens(t_token *tokens);
const char	*token_type_to_string(t_token_type type);

// args_utils.c
int	count_args(char **args);

#endif