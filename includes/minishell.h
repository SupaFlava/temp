/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:18:35 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/06/06 13:10:39 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# include "signals.h"
# include "libft.h"
# include "parser.h"
# include "typedefs.h"
# include "env.h"
# include "utils.h"
# include "builtins.h"
# include "lexer.h"
# include "execute.h"

// function prototypes
int	run_builtin(t_command *cmd, t_mshell *shell);
void	print_commands(t_command *cmd);


#endif