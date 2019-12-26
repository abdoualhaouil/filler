/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:14:25 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/25 03:11:29 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_queue
{
	t_list	*front;
	t_list	*rear;
	int		lenght;
}					t_queue;

typedef	struct		s_best_score
{
	int		index_coul;
	int		index_line;
	int		*final_postion;
	int		best;
}					t_best_score;

typedef	struct	s_piece
{
	int		*x;
	int		*y;
	int		len;
}				t_piece;

typedef	struct	s_stock
{
	int		**map;
	t_list	*my_piece;
	t_piece	*piece;
	int		len_coul;
	int		len_line;
	int		len;
}				t_stock;

typedef	struct		s_coord
{
	int				**map;
	int				x;
	int				y;
	int				value;
	int				len_coul;
	int				len_line;
	t_queue			*queue;
}					t_coord;

void				ft_solve(t_stock *stock);
int					ft_read_map(void);
t_piece				*ft_piece(t_piece *piece);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
t_list				*stack_pop(t_list *list);
t_list				*stack_push(t_list *list, void *content, size_t size);
void				*de_queue(t_queue *queue);
void				en_queue(void *content, size_t size, t_queue *queue);

#endif
