/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:18:35 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/08 17:34:30 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "signals.h"
# include "libft.h"
# include "parse.h"
# include "typedefs.h"
# include "env.h"
# include "utils.h"
# include "builtins.h"

int run_builtin(t_command *cmd, t_mshell *shell);

# include "lexer.h"
#endif