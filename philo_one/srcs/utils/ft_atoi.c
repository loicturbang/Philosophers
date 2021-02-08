/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:58:16 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 13:01:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static size_t		ft_atoi_2(const char *str, int *neg)
{
	int		i;
	size_t	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result);
}

int					ft_atoi(const char *str)
{
	int		neg;
	size_t	result;

	neg = 1;
	if (!str)
		return (-1);
	result = ft_atoi_2(str, &neg);
	if (result > 9223372036854775807)
	{
		if (neg == 1)
			return (-1);
		if (neg == -1)
			return (0);
	}
	return ((int)result * neg);
}
