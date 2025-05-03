/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:28 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/03 16:20:28 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *line;
	t_mshell shell;

	ft_bzero(&shell, sizeof(t_mshell));
    setup_signals();
	init_env(&shell ,envp);
	
    while (1)
	{
        line = read_input();
        if (line && *line)
		    add_history(line);
        
		ft_printf("Got: %s\n", line);
		free(line);
	}
	//rl_clear_history();
	clear_history(); // this is for mac
    return (0);
}