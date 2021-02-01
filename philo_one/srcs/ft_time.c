/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:49:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 10:34:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned long		get_ms_time(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long		get_delta_time(t_philo *philo)
{
	static unsigned long start_time = 0;

	if (!start_time)
	{
		gettimeofday(&philo->time_start, NULL);
		start_time = get_ms_time(philo->time_start);
		return (start_time);
	}
	gettimeofday(&philo->time_actual, NULL);
	return (get_ms_time(philo->time_actual) - start_time);
}

void				set_starve_time(t_philo *philo, int type)
{
	struct timeval	t_val;

	if (type == INIT)
	{
		gettimeofday(&t_val, NULL);
		philo->starve_t_start = get_ms_time(t_val);
		philo->starve_t_delta = 0;
	}
	else if (type == DELTA)
	{
		gettimeofday(&t_val, NULL);
		philo->starve_t_delta = get_ms_time(t_val) - philo->starve_t_start;
	}
}

void				wait_ms(unsigned long ms_wait, t_philo *p)
{
	unsigned long start_time;
	unsigned long actual_time;

	start_time = get_delta_time(p);
	actual_time = start_time;
	while (actual_time - start_time < ms_wait)
	{
		usleep(250);
		actual_time = get_delta_time(p);
	}
}
