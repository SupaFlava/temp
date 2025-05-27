/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 15:42:35 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/27 23:02:51 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int run_builtin(t_command *cmd, t_mshell *shell)
{
    if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
        return builtin_cd(shell, cmd->args);
    else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
        return builtin_pwd(shell);
	else if (ft_strncmp(cmd->args[0], "echo",ft_strlen(cmd->args[0])) == 0)
		return(builtin_echo(shell, cmd->args));
	else if (ft_strncmp(cmd->args[0], "env",ft_strlen(cmd->args[0])) == 0)
		return(builtin_env(shell, cmd->args));
	else
		return (0);
}


void	print_commands(t_command *cmd_list)
{
	int i;
	int count;

	count = 0;
	while (cmd_list)
	{
		ft_printf("=== Command %d ===\n", count);
		if (cmd_list->args)
		{
			i = 0;
			while (cmd_list->args[i])
			{
				ft_printf("arg[%d]: %s\n", i, cmd_list->args[i]);
				i++;
			}
		}
		else
			ft_printf("args: (none)\n");

		ft_printf("infile: %s\n", cmd_list->infile ? cmd_list->infile : "(none)");
		ft_printf("outfile: %s\n", cmd_list->outfile ? cmd_list->outfile : "(none)");
		ft_printf("append: %d\n", cmd_list->append);
		ft_printf("is_builtin: %d\n", cmd_list->is_builtin);
		ft_printf("next: %s\n", cmd_list->next ? "yes" : "no");
		ft_printf("\n");

		cmd_list = cmd_list->next;
		count++;
	}
}
