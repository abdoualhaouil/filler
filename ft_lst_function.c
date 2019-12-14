/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:22:26 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/13 06:21:01 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
		new->next = NULL;
		return (new);
	}
	if (!(new->content = (void *)malloc(content_size)))
	{
		free(new);
		return (NULL);
	}
	ft_memcpy(new->content, content, content_size);
	new->content_size = content_size;
	new->next = NULL;
	return (new);
}

void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	(*del)((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*next;
	t_list		*head;

	head = (*alst);
	while ((*alst)->next != NULL)
	{
		next = head->next;
		(*del)(head->content, head->content_size);
		free(head);
		head = next;
	}
	(*alst) = NULL;
}
