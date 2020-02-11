/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 04:52:59 by aalhaoui          #+#    #+#             */
/*   Updated: 2020/01/03 09:12:08 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int r;
	int s;

	r = 0;
	s = 1;
	if (!str)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		if (*(str + 1) == '+')
			return (0);
		s *= -1;
		str++;
	}
	if (*str == '+')
		str++;
	while (*str > 47 && *str < 58)
	{
		r = r * 10 + *str - 48;
		str++;
	}
	return (r * s);
}
