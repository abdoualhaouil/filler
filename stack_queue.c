/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:40:42 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/14 11:16:19 by aalhaoui         ###   ########.fr       */
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
	tmp = NULL;
	return (list);
}

void		*queue_pop(t_list *list)
{
	t_list	*tmp;
	void	*content_ret;

	content_ret = NULL;
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	content_ret = (void *)malloc(sizeof(void) * tmp->content_size);
	ft_memcpy(content_ret, tmp->content, tmp->content_size);
	ft_memdel(&(tmp->content));
	free(tmp);
	tmp = NULL;
	return (content_ret);
}

t_list		*stack_push(t_list *list, void *content, size_t size)
{
	t_list		*new;

	if (!(new = ft_lstnew(content, size)))
		return (NULL);
	(list != NULL) && (new->next = list);
	(list == NULL) && (new->next = NULL);
	return (new);
}
