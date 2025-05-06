/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:39:02 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/05 12:28:38 by rmhazres         ###   ########.fr       */
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