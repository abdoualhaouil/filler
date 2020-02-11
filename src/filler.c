/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 06:01:30 by aalhaoui          #+#    #+#             */
/*   Updated: 2020/01/04 16:05:06 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

static	t_best_score	*ft_initialize(void)
{
	t_best_score	*s;

	if (!(s = (t_best_score *)malloc(sizeof(t_best_score))))
		return (NULL);
	if (!(s->final_postion = (int *)malloc(sizeof(int) * 2)))
		return (NULL);
	(s->final_postion)[0] = 0;
	(s->final_postion)[1] = 0;
	s->best = 2147483647;
	return (s);
}

static	void			ft_free_best(t_best_score *final, t_best_score *s)
{
	free(s->final_postion);
	free(s);
	free(final->final_postion);
	free(final);
}

static	t_best_score	*ft_filler_tmp(t_best_score *final,
			t_best_score *s, int *r)
{
	final->best = s->best;
	(final->final_postion)[0] = (s->final_postion)[0];
	(final->final_postion)[1] = (s->final_postion)[1];
	(*r)++;
	return (final);
}

int						ft_filler(t_stock *stock, t_list *list)
{
	int				i0;
	int				j0;
	int				r;
	t_best_score	*final;
	t_best_score	*s;

	r = 0;
	final = ft_initialize();
	s = ft_initialize();
	list = stock->my_piece;
	while (list != NULL)
	{
		s->best = 2147483647;
		i0 = ((int *)list->content)[0];
		j0 = ((int *)list->content)[1];
		s = ft_find_best_position(stock, i0, j0, s);
		if (final->best > s->best)
			final = ft_filler_tmp(final, s, &r);
		list = list->next;
	}
	ft_printf("%d %d\n", final->final_postion[0], final->final_postion[1]);
	ft_free_best(final, s);
	if (r == 0)
		return (1);
	return (0);
}
