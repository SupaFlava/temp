/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:22:37 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/08 14:32:26 by rmhazres         ###   ########.fr       */
=======
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 11:22:37 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/08 15:45:18 by jbaetsen      ########   odam.nl         */
>>>>>>> 98c9e99b789698c80b7911da8ff1b62d06c8fe28
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H


<<<<<<< HEAD
int	shell_init(t_mshell *shell);
void	*ft_malloc_s(t_mshell *shell, size_t size, t_mem_t type);
void	ft_free(t_mshell *shell, t_mem_t type);
=======
// includes 
# include "libft.h"
# include "typedefs.h"

// function prototypes
// shell_init.c
int		shell_init(t_mshell *shell);

// str_utils.c
char	*ft_strndup(const char *str, size_t n);
char 	*ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *str1, const char *str2);

// list_utils.c
void		print_tokens(t_token *tokens);
void		free_tokens(t_token *tokens);
const char *token_type_to_string(t_token_type type);

>>>>>>> 98c9e99b789698c80b7911da8ff1b62d06c8fe28

# endif