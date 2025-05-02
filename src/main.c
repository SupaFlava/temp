/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 14:23:28 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/02 15:31:05 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	//using_history();
	char *line;

    setup_signals();
    line = readline("Our Shell >");
    if (!line)
    {
        printf("exiting minishell\n");
        exit(0);        
    }
	
    while (line != NULL)
	{
		ft_printf("Got: %s\n", line);
		add_history(line);
		free(line);
	}
	rl_clear_history();
    return (0);
}