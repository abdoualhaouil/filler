/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:14:25 by aalhaoui          #+#    #+#             */
/*   Updated: 2020/01/04 15:16:00 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_queue
{
	t_list			*front;
	t_list			*rear;
	int				lenght;
}					t_queue;

typedef	struct		s_best_score
{
	int				index_coul;
	int				index_line;
	int				*final_postion;
	int				best;
}					t_best_score;

typedef	struct		s_piece
{
	int				*x;
	int				*y;
	int				len;
}					t_piece;

typedef	struct		s_stock
{
	int				**map;
	t_list			*my_piece;
	t_piece			*piece;
	int				len_coul;
	int				len_line;
	int				len;
	int				b;
	int				i;
	int				j;
}					t_stock;

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

int					ft_filler(t_stock *stock, t_list *list);
void				ft_free_two(void *str, void *str1);
int					ft_read_map(char player, t_stock *stock, t_queue *queue);
t_piece				*ft_piece(t_piece *piece);
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*stack_push(t_list *list, void *content, size_t size);
void				*de_queue(t_queue *queue);
void				en_queue(void *content, size_t size, t_queue *queue);
void				ft_free_stock(t_stock *stock);
int					**ft_set_heatmap(t_stock *stock, t_queue *queue);
t_stock				*ft_get_len(t_stock *stock);
t_stock				*ft_stock_heatmap(t_stock *stock,
						t_queue **queue, char player, int b);
t_best_score		*ft_find_best_position(t_stock *stock,
	int i0, int j0, t_best_score *s);
int					**allocat_map(int row, int col);

#endif
