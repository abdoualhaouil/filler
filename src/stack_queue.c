/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:40:42 by aalhaoui          #+#    #+#             */
/*   Updated: 2020/01/04 15:13:11 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

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

void		*de_queue(t_queue *queue)
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
		free((queue->front->content));
		free((queue->front));
		queue->front = NULL;
		queue->rear = NULL;
	}
	else
	{
		tmp = (queue->front);
		(queue->front) = (queue->front)->next;
		free(tmp->content);
		free(tmp);
	}
	return (de_queue_ret);
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
