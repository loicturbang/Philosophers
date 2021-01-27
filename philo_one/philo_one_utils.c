/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:26:54 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 15:47:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			print_status(unsigned long long ms, int philo_id, int status)
{
	ft_putnbr_ull(ms);
	write(1, "ms ", 3);
	ft_putnbr(philo_id);
	if (status == SLEEP)
		ft_putstr(" is sleeping\n");
	else if (status == EAT)
		ft_putstr(" is eating\n");
	else if (status == FORK)
		ft_putstr(" has taken a fork\n");
	else if (status == THINK)
		ft_putstr(" is thinking\n");
	else if (status == DEAD)
		ft_putstr(" died\n");
}
