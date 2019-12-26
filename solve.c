/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 11:04:18 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/26 04:26:10 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static	t_piece	*get_piece(t_piece *piece, int lenp_coul, int lenp_line)
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
		get_next_line(0, &buff);
		j = -1;
		while (++j < lenp_coul)
		{
			if (buff[j] == '*')
			{
				piece->x[k] = i;
				piece->y[k] = j;
				piece->len += 1;
				k++;
			}
		}
		free(buff);
	}
	return (piece);
}

t_piece				*ft_piece(t_piece *piece)
{
	char	*buff;
	int		lenp_coul;
	int		lenp_line;

	piece = NULL;
	lenp_coul = 0;
	get_next_line(0, &buff);
	lenp_line = ft_atoi(buff + 6);
	while (buff[lenp_coul + 6] != ' ')
		lenp_coul++;
	lenp_coul = ft_atoi(buff + 6 + lenp_coul);
	free(buff);
	piece = (t_piece *)malloc(sizeof(t_piece));
	piece->x = (int *)malloc(sizeof(int) * lenp_line * lenp_coul);
	piece->y = (int *)malloc(sizeof(int) * lenp_line * lenp_coul);
	piece = get_piece(piece, lenp_coul, lenp_line);
	return (piece);
}

int			ft_set_piece(t_stock *stock, int i0, int j0, int k0)
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

static	int		*ft_final_postion(t_best_score *s, t_stock *stock, int k1)
{
	s->final_postion = (int *)malloc(sizeof(int) * 2);
	s->best = stock->map[s->index_line][s->index_coul];
	dprintf(2, "%d\n", s->best);
	(s->final_postion)[0] = s->index_line - stock->piece->x[k1];
	(s->final_postion)[1] = s->index_coul - stock->piece->y[k1];
	return (s->final_postion);
}

static	t_best_score	*ft_find_best_position(t_stock *stock, int i0, int j0)
{
	t_best_score	*s;
	int				i1;
	int				k1;
	int				j1;
	int				k0;

	k0 = -1;
	s = (t_best_score *)malloc(sizeof(t_best_score));
	s->best = 2147483647;
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
					s->final_postion = ft_final_postion(s, stock, k1);
			}
	}
	return (s);
}

void	ft_solve(t_stock *stock)
{
	int				i0;
	int				j0;
	t_best_score	*final;
	t_best_score	*s;

	final = (t_best_score *)malloc(sizeof(t_best_score));
	final->best = 2147483647;
	final->final_postion = (int *)malloc(sizeof(int) * 2);
	(final->final_postion)[0] = 0;
	(final->final_postion)[1] = 0;
	while (stock->my_piece != NULL)
	{
		i0 = ((int *)stock->my_piece->content)[0];
		j0 = ((int *)stock->my_piece->content)[1];
		s = ft_find_best_position(stock, i0, j0);
		if (final->best > s->best)
		{
			free(final->final_postion);
			final->final_postion = (int *)malloc(sizeof(int) * 2);
			final->best = s->best;
			(final->final_postion)[0] = (s->final_postion)[0];
			(final->final_postion)[1] = (s->final_postion)[1];
		}
		stock->my_piece = stock->my_piece->next;
	}
	ft_printf("%d %d\n", final->final_postion[0], final->final_postion[1]);
	free(final->final_postion);
	free(final);
}

int		main(void)
{
	ft_read_map();
	return (0);
}
