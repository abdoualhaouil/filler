/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heatmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 05:54:47 by aalhaoui          #+#    #+#             */
/*   Updated: 2020/01/04 15:13:06 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

int				**allocat_map(int row, int col)
{
	int i;
	int **ret;

	i = 0;
	if (!(ret = (int **)ft_memalloc(sizeof(int*) * row)))
		return (NULL);
	while (i < row)
	{
		if (!(ret[i] = (int *)ft_memalloc(sizeof(int) * col)))
			return (NULL);
		i++;
	}
	return (ret);
}

static int		**ft_check_box(int **map, t_coord *coord, int x, int y)
{
	int		*box;

	if (coord->x + x < coord->len_line && coord->y + y < coord->len_coul
		&& coord->x + x >= 0 && coord->y + y >= 0
		&& map[coord->x + x][coord->y + y] == 2147483646)
	{
		if (!(box = (int *)malloc(sizeof(int) * 3)))
			return (NULL);
		box[0] = coord->value;
		box[1] = coord->x + x;
		box[2] = coord->y + y;
		map[coord->x + x][coord->y + y] = coord->value;
		en_queue(box, sizeof(int ) * 3, coord->queue);
		free(box);
	}
	return (map);
}

int				**ft_set_heatmap(t_stock *stock, t_queue *queue)
{
	t_coord		*coord;
	void		*tab;

	while (queue->front != NULL)
	{
		if (!(coord = (t_coord *)malloc(sizeof(t_coord))))
			return (NULL);
		tab = de_queue(queue);
		coord->value = ((int *)tab)[0] + 1;
		coord->x = ((int *)tab)[1];
		coord->y = ((int *)tab)[2];
		coord->len_coul = stock->len_coul;
		coord->len_line = stock->len_line;
		coord->queue = queue;
		stock->map = ft_check_box(stock->map, coord, 0, 1);
		stock->map = ft_check_box(stock->map, coord, 0, -1);
		stock->map = ft_check_box(stock->map, coord, -1, 0);
		stock->map = ft_check_box(stock->map, coord, -1, 1);
		stock->map = ft_check_box(stock->map, coord, -1, -1);
		stock->map = ft_check_box(stock->map, coord, 1, 0);
		stock->map = ft_check_box(stock->map, coord, 1, 1);
		stock->map = ft_check_box(stock->map, coord, 1, -1);
		ft_free_two(coord, tab);
	}
	return (stock->map);
}
