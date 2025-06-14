/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:42:35 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/10 13:09:14 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


// int run_builtin(t_command *cmd, t_mshell *shell)
// {
// 	if (!cmd)
	//	return (0);
   // if (ft_strcmp(cmd->args[0], "cd") == 0)
//         return builtin_cd(shell, cmd->args);
//     else if (ft_strcmp(cmd->args[0], "pwd") == 0)
//         return builtin_pwd(shell);
// 	else if (ft_strcmp(cmd->args[0], "echo") == 0)
// 		return(builtin_echo(shell, cmd->args));
// 	else if (ft_strcmp(cmd->args[0], "env") == 0)
// 		return(builtin_env(shell, cmd->args));
// 	else if (ft_strcmp(cmd->args[0], "exit") == 0)
// 		return(builtin_exit(shell, cmd->args));
// 	else if (ft_strcmp(cmd->args[0], "unset") == 0)
// 		return(builtin_unset(shell, cmd->args));
// 	else
// 		return (0);
// }

void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("Command:\n");
		i = 0;
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("  arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		else
			printf("  args: (null)\n");
		printf("  infile: %s\n", cmd->infile ? cmd->infile : "(null)");
		printf("  outfile: %s\n", cmd->outfile ? cmd->outfile : "(null)");
		printf("  append: %d\n", cmd->append);
		printf("  heredoc_delimiter: %s\n", cmd->delimiter ? cmd->delimiter : "(null)");
		printf("  is_heredoc: %d\n", cmd->is_heredoc);
		printf("--------------------------\n");
		cmd = cmd->next;
	}
}
