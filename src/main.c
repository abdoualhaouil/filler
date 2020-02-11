/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 04:44:53 by aalhaoui          #+#    #+#             */
/*   Updated: 2020/01/04 15:12:52 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

void		ft_free_two(void *str, void *str1)
{
	free(str);
	free(str1);
}

void		ft_free_stock(t_stock *stock)
{
	int			i;
	t_list		*next;
	t_list		*head;

	i = -1;
	while (++i < stock->len_line)
		free((stock->map)[i]);
	free(stock->map);
	free(stock->piece->x);
	free(stock->piece->y);
	free(stock->piece);
	head = stock->my_piece;
	while ((head != NULL))
	{
		next = head->next;
		free(head->content);
		free(head);
		head = next;
	}
	stock->my_piece = NULL;
	free(stock);
	stock = NULL;
}

int			ft_read_map(char player, t_stock *stock, t_queue *queue)
{
	t_list	*list;
	int		r;

	r = 0;
	list = NULL;
	if (!(stock = ft_get_len(stock)))
		return (1);
	if (stock->len_coul <= 0 || stock->len_line <= 0)
		return (1);
	if (stock->len_coul == 17 && player == 'O' && (stock->b = 1))
		stock = ft_stock_heatmap(stock, &queue, player, stock->b);
	else
		stock = ft_stock_heatmap(stock, &queue, player, stock->b);
	stock->map = ft_set_heatmap(stock, queue);
	if (!(stock->piece = ft_piece(stock->piece)))
		return (1);
	r = ft_filler(stock, list);
	ft_free_stock(stock);
	free(queue);
	if (r == 1)
		return (1);
	return (0);
}

int			main(void)
{
	t_stock	*stock;
	t_queue	*queue;
	char	*buff;
	char	player;

	if (get_next_line(0, &buff) != 1)
		return (-1);
	player = (ft_strstr(buff, "p1") ? 'X' : 'O');
	free(buff);
	while (1)
	{
		if (!(stock = (t_stock *)ft_memalloc(sizeof(t_stock))))
			return (-1);
		if (!(queue = (t_queue *)ft_memalloc(sizeof(t_queue))))
			return (-1);
		if (ft_read_map(player, stock, queue) == 1)
			break ;
	}
	return (0);
}
