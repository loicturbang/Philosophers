/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:34:00 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 13:49:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			ft_count_num(unsigned long n)
{
	unsigned long	div;
	int				i;

	i = 0;
	div = 1;
	while (div)
	{
		div = n / 10;
		n = div;
		i++;
	}
	return (i);
}

char		*ft_itoa(unsigned long num)
{
	char			*str;
	unsigned long	div;
	char			mod;
	int				i;

	i = ft_count_num(num);
	str = malloc(sizeof(char) * (i + 1));
	div = 1;
	str[i--] = '\0';
	while (div)
	{
		div = num / 10;
		mod = num % 10;
		mod += 48;
		num = div;
		str[i] = mod;
		i--;
	}
	return (str);
}
