/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 06:09:00 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/14 03:37:30 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		**ft_stock_heatmap(t_list **list, int len_line, int len_coul)
{
	int		**map;
	char	*buff;
	int		*coord;
	int		i;
	int		j;

	i = 0;
	map = (int **)malloc(sizeof(int *) * len_line);
	while ((i < len_line) && get_next_line(0, &buff))
	{
		map[i] = (int *)malloc(sizeof(int) * len_coul);
		j = 3;
		while (++j < len_coul + 4)
		{
			(buff[j] == '.') && (map[i][j - 4] = -1);
			(buff[j] == 'X' || buff[j] == 'x') && (map[i][j - 4] = -2);
			(buff[j] == 'O' || buff[j] == 'o') && (map[i][j - 4] = -3);
			if (buff[j] == 'X')
			{
				coord = (int *)malloc(sizeof(int) * 3);
				coord[0] = 0;
				coord[1] = i;
				coord[2] = j - 4;
				(*list) = stack_push((*list), coord, sizeof(int ) * 3);
			}
		}
		i++;
	}
	return (map);
}

int		**ft_check_box(t_coord *coord, t_list **list, int x, int y)
{
	int		*box;

	if (coord->x + x < coord->len_coul && coord->y + y < coord->len_line
		&& coord->map[coord->x + x][coord->y + y] == -1)
	{
		box = (int *)malloc(sizeof(int) * 3);
		box[2] = coord->x + 1;
		box[2] = coord->y + 1;
		(coord->map)[coord->x + x][coord->y + y] += 1;
		(*list) = stack_push((*list), coord, sizeof(int ) * 3);
	}
	return (coord->map);
}

int		**ft_set_heatmap(int **map, t_list *list, int len_line, int len_coul)
{
	t_coord		*coord;
	void			*tab;

	coord = (t_coord *)malloc(sizeof(t_coord));
	// while (list != NULL)
	// {
		tab = queue_pop(list);
		dprintf(2, "%d\n", list != NULL);
		coord->x = ((int *)tab)[1];
		coord->y = ((int *)tab)[2];
		coord->len_coul = len_coul;
		coord->len_line = len_line;
		coord->map = map;
		map = ft_check_box(coord, &list, 0, 1);
	 	map = ft_check_box(coord, &list, 0, -1);
		map = ft_check_box(coord, &list, -1, 0);
		map = ft_check_box(coord, &list, -1, 1);
		map = ft_check_box(coord, &list, -1, -1);
		map = ft_check_box(coord, &list, 1, 0);
		map = ft_check_box(coord, &list, 1, 1);
		map = ft_check_box(coord, &list, 1, -1);
		while(list != NULL)
		{
			dprintf(2, "%d\n", ((int *)(list->content))[1]);
			list = list->next;
		}
	return (map);
}

int		ft_read_map(void)
{
	t_list	*list;
	char	*buff;
	int		**map;
	int		len_coul;
	int		len_line;
	int		player;
	// int i = 0, j;

	len_coul = 0;
	list = NULL;
	if (!(get_next_line(0, &buff)))
		return (-1);
	player = buff[10] - '0';
	free(buff);
	if (get_next_line(0, &buff) == -1)
		return (-1);
	len_line = ft_atoi(buff + 8);
	while (buff[len_coul + 8] != ' ')
		len_coul++;
	len_coul = ft_atoi(buff + 8 + len_coul);
	free(buff);
	if (!(get_next_line(0, &buff)))
		return (-1);
	free(buff);
	map = ft_stock_heatmap(&list, len_line, len_coul);
	map = ft_set_heatmap(map, list, len_coul, len_line);
	// while (i < len_line)
	// {
	// 	j = 0;
	// 	while (j < len_coul)
	// 	{
	// 		dprintf(2, "%d", map[i][j]);
	// 		j++;
	// 	}
	// 	dprintf(2, "\n");
	// 	i++;
	// }
	return (0);
}

int main()
{
	ft_read_map();
	return (0);
}