/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 11:22:37 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/08 15:45:18 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H


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


# endif