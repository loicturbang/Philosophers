/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:44:40 by user42            #+#    #+#             */
/*   Updated: 2021/02/10 10:08:17 by user42           ###   ########.fr       */
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
	char				*str;
	unsigned int		size;

	i = 0;
	size = ft_strlen(src);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void			ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void			ft_putnbr_ul(unsigned long n)
{
	unsigned long		div;
	char				mod;

	div = n / 10;
	mod = n % 10;
	if (div)
		ft_putnbr_ul(div);
	mod += 48;
	write(1, &mod, 1);
}
