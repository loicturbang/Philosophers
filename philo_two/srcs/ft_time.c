/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:49:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 14:16:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

unsigned long		get_ms_time(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long		get_delta_time(void)
{
	static unsigned long	start_time = 0;
	struct timeval			time_start;
	struct timeval			time_actual;

	if (!start_time)
	{
		gettimeofday(&time_start, NULL);
		start_time = get_ms_time(time_start);
		return (start_time);
	}
	gettimeofday(&time_actual, NULL);
	return (get_ms_time(time_actual) - start_time);
}

void				wait_ms(unsigned long ms_wait)
{
	unsigned long start_time;
	unsigned long actual_time;

	start_time = get_delta_time();
	actual_time = start_time;
	usleep((ms_wait * 0.8) * 1000);
	while (actual_time - start_time < ms_wait)
	{
		usleep(250);
		actual_time = get_delta_time();
	}
}
