/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/09 09:32:57 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** sem_wait -> remove 1 from semaphore (take 1 fork)
** sem_wait 2 times (2 forks)
** sem_post --> give fork back
*/

void	philo_life(t_p *p, t_philo *philo)
{
	get_delta_time();
	while (p->life)
	{
		sem_wait(p->forks);
		sem_wait(p->forks);
		print_status(get_delta_time(), philo->id, FORK, p);
		print_status(get_delta_time(), philo->id, FORK, p);
		print_status(get_delta_time(), philo->id, EAT, p);
		if (philo->nb_eat >= p->must_eat_nb - 1 && p->must_eat_nb != -1)
			sem_post(philo->must_eat);
		philo->nb_eat++;
		philo->last_eat = get_delta_time();
		wait_ms(p->tt_eat);
		sem_post(p->forks);
		sem_post(p->forks);
		print_status(get_delta_time(), philo->id, SLEEP, p);
		wait_ms(p->tt_sleep);
		print_status(get_delta_time(), philo->id, THINK, p);
	}
	exit(0);
}

void	*init_philo(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	if (philo->id + 1 == p->nb_philos)
		sem_post(p->sem_fork_sync_philo);
	else
	{
		sem_wait(p->sem_fork_sync_philo);
		sem_post(p->sem_fork_sync_philo);
	}
	philo_life(p, philo);
	return (NULL);
}
