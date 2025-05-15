/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:39:02 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/15 13:32:20 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    env_add_back(t_env **head, t_env *new_node)
{
    t_env *tmp;
    
    if (!head || !new_node)
        return;
    if (*head == NULL)
    {
        *head = new_node;
        return ; 
    }
    tmp = *head;
    while (tmp->next != NULL)
       tmp = tmp->next;
    tmp->next = new_node;
}

void env_print(t_mshell *shell)
{
	t_env *temp;
	
	temp = shell->env_list;


	while (temp != NULL)
	{
		if (temp->key != NULL)
			ft_printf("%s=",temp->key);
		if (temp->value != NULL)
			ft_printf("%s\n",temp->value);
		temp = temp->next;
	}
}
