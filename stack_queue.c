/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:40:42 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/13 03:45:53 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_list		*stack_pop(t_list *list)
{
	t_list		*tmp;

	tmp = list->next;
	list->next = tmp->next;
	ft_memdel(&(tmp->content));
	free(tmp);
	return (list);
}

void		*queue_pop(t_list *list)
{
	t_list	*tmp;
	void	*content_ret;

	tmp = list;
	dprintf(2, "fsadfads\n\n");
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	content_ret = (void *)malloc(sizeof(void) * tmp->next->content_size);
	ft_memcpy(content_ret, tmp->next->content, tmp->next->content_size);
	free(tmp->next->content);
	free(tmp->next);
	tmp->next = NULL;
	return (content_ret);
}

t_list		*stack_push(t_list *list, void *content, int size)
{
	t_list		*new;

	if (!(new = ft_lstnew(content, size * sizeof(int))))
		return (NULL);
	new->next = list->next;
	list->next = new;
	return (list);
}
