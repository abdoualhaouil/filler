/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 06:09:00 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/26 04:18:36 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_stock	*ft_stock_heatmap(int len_line, int len_coul, t_queue *queue,
		char player)
{
	t_stock	*stock;
	char	*buff;
	int		*coord;
	int		i;
	int		j;

	i = 0;
	stock = (t_stock *)malloc(sizeof(t_stock));
	(stock->map) = (int **)malloc(sizeof(int *) * len_line);
	stock->my_piece = NULL;
	stock->len = 0;
	while ((i < len_line) && (get_next_line(0, &buff) == 1))
	{
		(stock->map)[i] = (int *)malloc(sizeof(int) * len_coul);
		j = 3;
		while (++j < len_coul + 4)
		{
			(buff[j] == '.') && ((stock->map)[i][j - 4] = 2147483646);
			(buff[j] == 'X' || buff[j] == 'x') && ((stock->map)[i][j - 4] = -2);
			(buff[j] == 'O' || buff[j] == 'o') && ((stock->map)[i][j - 4] = -3);
			if (buff[j] == player || buff[j] == player - 32)
			{
				coord = (int *)malloc(sizeof(int) * 3);
				coord[0] = -1;
				coord[1] = i;
				coord[2] = j - 4;
				en_queue(coord, sizeof(int ) * 3, queue);
				free(coord);
			}
			else if (buff[j] != '.')
			{
				coord = (int *)malloc(sizeof(int) * 2);
				coord[0] = i;
				coord[1] = j - 4;
				stock->my_piece = stack_push(stock->my_piece, coord, 8);
				stock->len += 1;
				free(coord);
			}
		}
		ft_strdel(&buff);
		i++;
	}
	return (stock);
}

static int		**ft_check_box(int **map, t_coord *coord, int x, int y)
{
	int		*box;

	if (coord->x + x < coord->len_line && coord->y + y < coord->len_coul
		&& coord->x + x >= 0 && coord->y + y >= 0
		&& map[coord->x + x][coord->y + y] == 2147483646)
	{
		box = (int *)malloc(sizeof(int) * 3);
		box[0] = coord->value;
		box[1] = coord->x + x;
		box[2] = coord->y + y;
		map[coord->x + x][coord->y + y] = coord->value;
		en_queue(box, sizeof(int ) * 3, coord->queue);
		free(box);
	}
	return (map);
}

static int		**ft_set_heatmap(int **map, int len_line, int len_coul,
	t_queue *queue)
{
	t_coord		*coord;
	void		*tab;

	while (queue->front != NULL)
	{
		coord = (t_coord *)malloc(sizeof(t_coord));
		tab = de_queue(queue);
		coord->value = ((int *)tab)[0] + 1;
		coord->x = ((int *)tab)[1];
		coord->y = ((int *)tab)[2];
		coord->len_coul = len_coul;
		coord->len_line = len_line;
		coord->queue = queue;
		map = ft_check_box(map, coord, 0, 1);
		map = ft_check_box(map, coord, 0, -1);
		map = ft_check_box(map, coord, -1, 0);
		map = ft_check_box(map, coord, -1, 1);
		map = ft_check_box(map, coord, -1, -1);
		map = ft_check_box(map, coord, 1, 0);
		map = ft_check_box(map, coord, 1, 1);
		map = ft_check_box(map, coord, 1, -1);
		free(coord);
		free(tab);
	}
	return (map);
}

int		ft_read_map(void)
{
	char	*buff;
	int		len_coul;
	int		len_line;
	char	player;
	t_queue	*queue;
	t_stock *stock;

	stock = (t_stock *)malloc(sizeof(t_stock));
	queue = (t_queue *)malloc(sizeof(t_queue));
	if (get_next_line(0, &buff) != 1)
		return (-1);
	free(buff);
	player = (buff[10] == '1') ? 'X' : 'O';
	while (1)
	{
		len_coul = 0;
		if (get_next_line(0, &buff) != 1)
			return (-1);
		len_line = ft_atoi(buff + 8);
		while (buff[len_coul + 8] != ' ')
			len_coul++;
		len_coul = ft_atoi(buff + 8 + len_coul);
		free(buff);
		if (get_next_line(0, &buff) != 1)
			return (-1);
		free(buff);
		queue->front = NULL;
		queue->rear = NULL;
		stock = ft_stock_heatmap(len_line, len_coul, queue, player);
		stock->map = ft_set_heatmap(stock->map, len_line, len_coul, queue);
		// free(queue);
		stock->len_coul = len_coul;
		stock->len_line = len_line;
		stock->piece = ft_piece((stock->piece));
		ft_solve(stock);
	}
	return (1);
}
