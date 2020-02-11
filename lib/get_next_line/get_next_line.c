/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:17:10 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/06/24 20:42:01 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_breakindex(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	return (i);
}

int		ft_store_buff(int fd, char **temp)
{
	char	*str;
	int		ret;
	char	buff[BUFF_SIZE + 1];

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		str = *temp;
		*temp = ft_strjoin(*temp, buff);
		ft_strdel(&str);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret == -1)
		ft_strdel(temp);
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static char		*tab[4865];
	int				ret;
	char			*temp;
	int				break_index;

	if (fd < 0 || fd > 4864 || !line)
		return (-1);
	if (!tab[fd])
		tab[fd] = ft_strnew(0);
	temp = ft_strdup(tab[fd]);
	ft_strdel(&tab[fd]);
	if ((ret = ft_store_buff(fd, &temp)) < 0)
		return (-1);
	break_index = ft_breakindex(temp);
	*line = ft_strsub(temp, 0, break_index);
	if (temp[break_index])
		tab[fd] = ft_strdup(temp + break_index + 1);
	ft_strdel(&temp);
	if (!**line && !tab[fd] && ret == 0)
	{
		ft_strdel(line);
		return (0);
	}
	return (1);
}
