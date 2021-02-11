/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/11 12:45:33 by lturbang         ###   ########.fr       */
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
	get_delta_time(p);
	while (p->life)
	{
		sem_wait(p->fork_check);
		sem_wait(p->forks);
		sem_wait(p->forks);
		add_print(p, get_print(get_delta_time(p), philo->id, FORK, p));
		add_print(p, get_print(get_delta_time(p), philo->id, FORK, p));
		add_print(p, get_print(get_delta_time(p), philo->id, EAT, p));
		if (philo->nb_eat >= p->must_eat_nb - 1 && p->must_eat_nb != -1 && \
													philo->sem_done == 0)
		{
			philo->sem_done = 1;
			sem_post(p->must_eat);
		}
		philo->nb_eat++;
		philo->last_eat = get_delta_time(p);
		wait_ms(p->tt_eat, p);
		sem_post(p->forks);
		sem_post(p->forks);
		sem_post(p->fork_check);
		add_print(p, get_print(get_delta_time(p), philo->id, SLEEP, p));
		wait_ms(p->tt_sleep, p);
		add_print(p, get_print(get_delta_time(p), philo->id, THINK, p));
	}
	exit(0);
}

void	*init_philo(void *arg)
{
	t_philo		*philo;
	t_p			*p;
	int			i;

	i = -1;
	philo = (t_philo *)arg;
	p = philo->p;
	if (philo->id + 1 == p->nb_philos)
	while (++i < (p->nb_philos * 3))
		sem_post(p->sem_fork_sync);
	else
		sem_wait(p->sem_fork_sync);
	philo_life(p, philo);
	return (NULL);
}
