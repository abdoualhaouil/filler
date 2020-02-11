/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:53:41 by aalhaoui          #+#    #+#             */
/*   Updated: 2020/01/04 15:57:12 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

static		t_stock	*ft_initialize_map(t_stock *stock, char *buff, char player,
	t_queue **queue)
{
	int		*coord;

	if (ft_toupper(buff[stock->j]) == player && (stock->b == 0))
	{
		if (!(coord = (int *)malloc(sizeof(int) * 3)))
			return (NULL);
		coord[0] = -1;
		coord[1] = stock->i;
		coord[2] = stock->j;
		en_queue(coord, sizeof(int ) * 3, (*queue));
		free(coord);
	}
	else if (buff[stock->j] != '.' && ft_toupper(buff[stock->j]) != player)
	{
		if (!(coord = (int *)malloc(sizeof(int) * 2)))
			return (NULL);
		coord[0] = stock->i;
		coord[1] = stock->j;
		stock->my_piece = stack_push(stock->my_piece, coord, 8);
		stock->len += 1;
		free(coord);
	}
	return (stock);
}

int					ft_stock_index(t_queue **queue)
{
	int *coord;

	if (!(coord = (int *)malloc(sizeof(int) * 3)))
		return (-1);
	coord[0] = -1;
	coord[1] = 0;
	coord[2] = 16;
	en_queue(coord, sizeof(int ) * 3, (*queue));
	free(coord);
	return (1);
}

t_stock				*tmp_stock_heat_map(t_stock *stock, char *buff, char player,
			t_queue **queue)
{
	if (buff[stock->j] == '.')
		(stock->map)[stock->i][stock->j] = 2147483646;
	if (buff[stock->j] == 'X' || buff[stock->j] == 'x')
		(stock->map)[stock->i][stock->j] = -2;
	if (stock->i == 0 && (buff[stock->j] == 'X' ||
		buff[stock->j] == 'O'))
		stock->b = 0;
	if (buff[stock->j] == 'O' || buff[stock->j] == 'o')
		(stock->map)[stock->i][stock->j] = -3;
	stock = ft_initialize_map(stock, buff, player, queue);
	return (stock);
}

t_stock				*ft_stock_heatmap(t_stock *stock, t_queue **queue,
			char player, int b)
{
	char	*buff;
	char	*tmp;

	if (!(stock->map = allocat_map(stock->len_line, stock->len_coul)))
		return (NULL);
	while ((stock->i < stock->len_line) && (get_next_line(0, &buff) == 1))
	{
		stock->j = -1;
		if (!(tmp = ft_strchr(buff, ' ')) || (int)ft_strlen(tmp + 1) <
			stock->len_coul)
			return (NULL);
		while (++(stock->j) < stock->len_coul)
			tmp_stock_heat_map(stock, tmp + 1, player, queue);
		(stock->i)++;
		free(buff);
	}
	if (stock->i != stock->len_line)
		return (NULL);
	(b == 1) && (ft_stock_index(queue));
	return (stock);
}

t_stock				*ft_get_len(t_stock *stock)
{
	char	*buff;
	char	*tmp;

	if (get_next_line(0, &buff) != 1)
		return (NULL);
	if (!(tmp = ft_strchr(buff, ' ')))
		return (NULL);
	stock->len_line = ft_atoi(tmp);
	stock->len_coul = ft_atoi(ft_strchr(tmp + 1, ' '));
	free(buff);
	if (get_next_line(0, &buff) != 1)
		return (NULL);
	free(buff);
	return (stock);
}
