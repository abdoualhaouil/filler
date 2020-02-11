/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 20:13:57 by aalhaoui          #+#    #+#             */
/*   Updated: 2020/01/04 15:12:56 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

static	t_piece			*get_piece(t_piece *piece, int lenp_coul, int lenp_line)
{
	char	*buff;
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	piece->len = 0;
	while (++i < lenp_line)
	{
		if (get_next_line(0, &buff) != 1)
			return (NULL);
		j = -1;
		while (++j < lenp_coul)
			if (buff[j] == '*')
			{
				piece->x[k] = i;
				piece->y[k] = j;
				piece->len += 1;
				k++;
			}
		free(buff);
	}
	return (piece);
}

t_piece					*ft_piece(t_piece *piece)
{
	char	*buff;
	char	*tmp;
	int		lenp_coul;
	int		lenp_line;

	piece = NULL;
	lenp_coul = 0;
	if ((get_next_line(0, &buff) != 1))
		return (NULL);
	tmp = ft_strchr(buff, ' ');
	lenp_line = ft_atoi(tmp);
	tmp = ft_strchr(tmp + 1, ' ');
	lenp_coul = ft_atoi(tmp);
	free(buff);
	if (!(piece = (t_piece *)malloc(sizeof(t_piece))))
		return (NULL);
	if (!(piece->x = (int *)malloc(sizeof(int) * lenp_line * lenp_coul)))
		return (NULL);
	if (!(piece->y = (int *)malloc(sizeof(int) * lenp_line * lenp_coul)))
		return (NULL);
	if (!(piece = get_piece(piece, lenp_coul, lenp_line)))
		return (NULL);
	return (piece);
}

static	int				ft_set_piece(t_stock *stock, int i0, int j0, int k0)
{
	int i1;
	int	j1;
	int k1;
	int index_coul;
	int index_line;

	k1 = -1;
	i1 = stock->piece->x[k0];
	j1 = stock->piece->y[k0];
	while (++k1 < stock->piece->len)
	{
		index_coul = j0 + stock->piece->y[k1] - j1;
		index_line = i0 + stock->piece->x[k1] - i1;
		if (k0 != k1)
		{
			if (!((index_coul < stock->len_coul) && (index_line <
					stock->len_line) && (index_coul >= 0) &&
					(index_line >= 0)) ||
						stock->map[index_line][index_coul] < 0)
				return (-1);
		}
	}
	return (1);
}

static t_best_score		*tmp_find_best_position(t_best_score *s, t_stock *stock,
	int k1)
{
	s->best = stock->map[s->index_line][s->index_coul];
	(s->final_postion)[0] = s->index_line - stock->piece->x[k1];
	(s->final_postion)[1] = s->index_coul - stock->piece->y[k1];
	return (s);
}

t_best_score			*ft_find_best_position(t_stock *stock,
	int i0, int j0, t_best_score *s)
{
	int				i1;
	int				k1;
	int				j1;
	int				k0;

	k0 = -1;
	while (++k0 < stock->piece->len)
	{
		k1 = -1;
		i1 = stock->piece->x[k0];
		j1 = stock->piece->y[k0];
		while (++k1 < stock->piece->len)
			if (k0 != k1)
			{
				s->index_coul = j0 + stock->piece->y[k1] - j1;
				s->index_line = i0 + stock->piece->x[k1] - i1;
				if (ft_set_piece(stock, i0, j0, k0) == -1)
					break ;
				if (stock->map[s->index_line][s->index_coul] < s->best)
					s = tmp_find_best_position(s, stock, k1);
			}
	}
	return (s);
}
