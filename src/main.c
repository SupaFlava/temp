/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:28 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/02 16:32:36 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

int main()
{
	//using_history();
	char *line;

    setup_signals();

	
    while (1)
	{
        line = read_input();
        if (line && *line)
		    add_history(line);
        
		ft_printf("Got: %s\n", line);
		free(line);
	}
	rl_clear_history();
    return (0);
}