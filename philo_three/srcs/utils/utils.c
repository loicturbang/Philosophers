/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:44:40 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 14:25:31 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

unsigned int	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

char			*ft_strdup(const char *src)
{
	int					i;
	char				*string;
	unsigned int		size;

	i = 0;
	size = ft_strlen(src);
	if (!(string = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (src[i])
	{
		string[i] = src[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

void			ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}
