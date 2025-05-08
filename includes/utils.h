/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:22:37 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/08 14:32:26 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H


int	shell_init(t_mshell *shell);
void	*ft_malloc_s(t_mshell *shell, size_t size, t_mem_t type);
void	ft_free(t_mshell *shell, t_mem_t type);

# endif