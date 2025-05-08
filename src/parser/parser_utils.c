/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:47:17 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/08 16:03:29 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *read_input(void)
{
    char    *line;
    
    line = readline("> ");
    if (!line)
    {
        ft_printf("exiting minishell\n");
        exit(0);
    }
    return (line);
}