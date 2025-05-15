/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:28 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/15 15:16:47 by rmhazres         ###   ########.fr       */
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
	t_command cmd = {
		.args = (char *[]){"cd" , "dsada", "ho", NULL}
	};

    while (1)
	{
        shell.line = read_input();
        if (shell.line && *shell.line)
		    add_history(shell.line);
		run_builtin(&cmd, &shell); // this is a tester
		shell.tokens = lexer(shell.line);
		free_tokens(shell.tokens);
		free(shell.line);
		shell.line = NULL;
		ft_free(&shell, MEM_TEMP);
	}
	rl_clear_history();
	ft_free(&shell, MEM_LONG);
	//clear_history(); // this for mac
    return (0);
}
