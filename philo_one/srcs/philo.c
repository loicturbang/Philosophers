/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 18:08:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Mutex lock -> take fork and lock it
** Mutex lock philo +1
** Mutex unlock, to give forks back after eat
*/

void	philo_eat(t_p *p, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&p->phil[(philo->id + 1) % p->nb_philos]->fork);
	if (p->life == 0)
		pthread_mutex_lock(&p->can_eat);
	add_print(p, get_print(get_delta_time(p), philo->id, FORK, p));
	add_print(p, get_print(get_delta_time(p), philo->id, FORK, p));
	add_print(p, get_print(get_delta_time(p), philo->id, EAT, p));
	philo->last_eat = get_delta_time(p);
	wait_ms(p->tt_eat, p);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&p->phil[(philo->id + 1) % p->nb_philos]->fork);
	philo->nb_eat++;
	if (philo->nb_eat >= p->must_eat_nb && p->must_eat_nb != -1)
	{
		p->finish_eat += 1;
		pthread_mutex_lock(&p->can_eat);
	}
}

void	philo_life(t_p *p, t_philo *philo)
{
	while (p->life)
	{
		philo_eat(p, philo);
		if (p->life == 0)
			pthread_mutex_lock(&p->can_eat);
		add_print(p, get_print(get_delta_time(p), philo->id, SLEEP, p));
		wait_ms(p->tt_sleep, p);
		if (p->life == 0)
			pthread_mutex_lock(&p->can_eat);
		add_print(p, get_print(get_delta_time(p), philo->id, THINK, p));
	}
}

void	*init_philo(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	if (philo->id + 1 == p->nb_philos)
		pthread_mutex_unlock(&p->sync);
	else
	{
		pthread_mutex_lock(&p->sync);
		pthread_mutex_unlock(&p->sync);
	}
	get_delta_time(p);
	philo_life(p, philo);
	return (NULL);
}
