/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 21:25:36 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Mutex lock -> take fork and lock it
** Mutex lock philo +1
** Mutex unlock, to give forks back after eat
*/

void	*init_philo(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	while (p->life)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&p->philos[(philo->id + 1) % p->nb_philos]->mutex);
		print_status(get_delta_time(philo), philo->id, FORK, p);
		print_status(get_delta_time(philo), philo->id, EAT, p);
		philo->last_eat = get_delta_time(philo);
		wait_ms(p->tt_eat, philo);
		philo->nb_eat++;
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&p->philos[(philo->id + 1) % p->nb_philos]->mutex);
		print_status(get_delta_time(philo), philo->id, SLEEP, p);
		wait_ms(p->tt_sleep, philo);
		print_status(get_delta_time(philo), philo->id, THINK, p);
	}
	return (NULL);
}
