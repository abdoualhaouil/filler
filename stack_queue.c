/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:40:42 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/26 03:12:54 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

t_list		*stack_push(t_list *list, void *content, size_t size)
{
	t_list		*new;

	if (!(new = ft_lstnew(content, size)))
		return (NULL);
	new->next = list;
	return (new);
}

void		en_queue(void *content, size_t size, t_queue *queue)
{
	t_list	*new;

	new = ft_lstnew(content, size);
	if (queue->front == NULL)
	{
		queue->front = new;
		queue->rear = new;
	}
	else
	{
		queue->rear->next = new;
		queue->rear = new;
	}
}

void	*de_queue(t_queue *queue)
{
	t_list		*tmp;
	void		*de_queue_ret;

	if ((queue->front) == NULL)
		return (NULL);
	de_queue_ret = (void *)malloc((queue->front)->content_size);
	ft_memcpy(de_queue_ret, (queue->front)->content,
		(queue->front)->content_size);
	if ((queue->front) == queue->rear)
	{
		free((queue->front));
		queue->front = NULL;
		queue->rear = NULL;
	}
	else
	{
		tmp = (queue->front);
		(queue->front) = (queue->front)->next;
		free(queue->front->content);
		free(tmp);
	}
	return (de_queue_ret);
}
