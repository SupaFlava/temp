/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 15:47:17 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/02 15:55:51 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *read_input(void)
{
    char    *line;
    
    line = readline("Our Shell > ");
    if (!line)
    {
        ft_printf("exiting minishell\n");
        exit(0);
    }
    return (line);
}