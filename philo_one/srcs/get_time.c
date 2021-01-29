/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:49:53 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 10:03:54 by user42           ###   ########.fr       */
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
