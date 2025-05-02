/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:30:25 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/02 15:23:19 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0); //clears current input buffer
    rl_on_new_line(); //tell readline a new line has started
    rl_redisplay(); // redisplay the prompt 
}

void    setup_signals(void)
{
    struct  sigaction sa;

    sa.sa_handler = handle_sigint; //sets the handler to use
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL); // this take care of ctrl + c

    sa.sa_handler = SIG_IGN;    
    sigaction(SIGQUIT, &sa, NULL);
    
}