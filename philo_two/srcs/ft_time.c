/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:49:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 10:57:24 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

unsigned long		get_ms_time(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long		get_delta_time(t_p *p)
{
	struct timeval			time_start;
	struct timeval			time_actual;

	if (!p->start_time)
	{
		gettimeofday(&time_start, NULL);
		p->start_time = get_ms_time(time_start);
		return (p->start_time);
	}
	gettimeofday(&time_actual, NULL);
	return (get_ms_time(time_actual) - p->start_time);
}

void				wait_ms(unsigned long ms_wait, t_p *p)
{
	unsigned long start_time;
	unsigned long actual_time;

	start_time = get_delta_time(p);
	actual_time = start_time;
	usleep((ms_wait * 0.8) * 1000);
	while (actual_time - start_time < ms_wait)
	{
		actual_time = get_delta_time(p);
		usleep(250);
	}
}
