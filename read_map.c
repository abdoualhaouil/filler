/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 06:09:00 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/13 03:50:51 by aalhaoui         ###   ########.fr       */
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
	while (get_next_line(0, &buff) && (i < len_line))
	{
		map[i] = (int *)malloc(sizeof(int) * len_coul);
		j = 3;
		while (buff[++j])
		{
			(buff[j] == '.') && (map[i][j] = -1);
			(buff[j] == 'X' || buff[j] == 'x') && (map[i][j] = -2);
			(buff[j] == 'O' || buff[j] == 'o') && (map[i][j] = -3);
			if (buff[j] == 'X')
			{
				coord = (int *)malloc(sizeof(int) * 2);
				coord[0] = i;
				coord[1] = j - 4;
				(*list) = stack_push((*list), coord, 2);
			}
			dprintf(2, "%d ", map[i][j]);
		}
		dprintf(2, "\n");
		i++;
	}
	return (map);
}

// int		**ft_check_box(t_coord *coord, t_list *list)
// {
// 	int		*box;

// 	if (coord->x < coord->len_coul && coord->y < coord->len_line
// 		&& coord->map[coord->x][coord->y] == -1)
// 	{
// 		box = (int *)malloc(sizeof(int) * 2);
// 		box[0] = coord->x + 1;
// 		box[1] = coord->y + 1;
// 		(coord->map[coord->x][coord->y]++) &&
// 			(list = stack_push(list, coord, 2));
// 	}
// 	return (coord->map);
// }

/*int		**ft_set_heatmap(int **map, t_list *list, int len_line, int len_coul)
{
	t_coord		*coord;
	void			*tab;

	coord = (t_coord *)malloc(sizeof(t_coord));

	dprintf(2, "%d\n", !(list->next != NULL));
	while (!(list->next != NULL))
	{
		dprintf(2, "fsadfads\n\n");
		tab = queue_pop(list);
		// dprintf(2, "%d\n", tab[0]);
		// coord->x = tab[0];
		// coord->y = tab[1];
		// dprintf(2, "<%d %d>\n", coord->x, coord->y);
		coord->len_coul = len_coul;
		coord->len_line = len_line;
		//ft_check_box(coord, list);
	}
	return (map);
}*/

int		ft_read_map(void)
{
	t_list	*list;
	char	*buff;
	int		**map;
	int		len_coul;
	int		len_line;
	int		player;

	len_coul = 0;
	if (!(list = ft_lstnew(NULL, 0)))
		return (-1);
	while (1)
	{
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
	//	map = ft_set_heatmap(map, list, len_coul, len_line);
		dprintf(2, "%d\n", ((int *)list->next->content)[0]);
	}
}

int main()
{
	ft_read_map();
	return (0);
}