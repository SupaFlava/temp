/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:28 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/06/05 15:44:42 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;

	(void)argc;
	(void)argv;

	shell_init(&shell);
    setup_signals();
	init_env(&shell ,envp);
	while (1)
	{
		shell.line = read_input();
		if (shell.line && *shell.line)
		{
			add_history(shell.line);
			shell.tokens = lexer(&shell);
			if (!shell.tokens)
				ft_printf("ERROR\n");
			// else
			// 	print_tokens(shell.tokens); // temp to see registered tokens
			shell.commands = parser(&shell);
			print_commands(shell.commands); // temp to see registered commands
		}
		execute_cmd(&shell);
		free(shell.line);
		shell.line = NULL;
		ft_free(&shell, MEM_TEMP);
	}
	rl_clear_history();
	//clear_history(); // this for mac
	return (0);
}
