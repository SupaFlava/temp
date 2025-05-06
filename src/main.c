/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:28 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/06 11:36:11 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_mshell shell;

	if (shell_init(&shell) == EXIT_FAILURE)
		return(EXIT_FAILURE);
    setup_signals();
	init_env(&shell ,envp);
    while (1)
	{
		
        shell.line = read_input();
        if (shell.line && *shell.line)
		    add_history(shell.line);
        
		ft_printf("Got: %s\n", shell.line);
		free(shell.line);
		shell.line = NULL;
	}
	rl_clear_history();
	//clear_history(); // this for mac
    return (0);
}