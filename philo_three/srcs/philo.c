/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 13:54:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_eat(t_p *p, t_philo *philo)
{
	sem_wait(p->fork_check);
	sem_wait(p->forks);
	sem_wait(p->forks);
	if (p->life == 0)
		sem_wait(p->can_eat);
	add_print(p, get_print(get_delta_time(p), philo->id, FORK, p));
	add_print(p, get_print(get_delta_time(p), philo->id, FORK, p));
	add_print(p, get_print(get_delta_time(p), philo->id, EAT, p));
	philo->last_eat = get_delta_time(p);
	wait_ms(p->tt_eat, p);
	sem_post(p->forks);
	sem_post(p->forks);
	sem_post(p->fork_check);
	philo->nb_eat++;
	if (philo->nb_eat >= p->must_eat_nb && p->must_eat_nb != -1)
		sem_wait(p->can_eat);
}

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
		philo_eat(p, philo);
		if (p->life == 0)
			sem_wait(p->can_eat);
		add_print(p, get_print(get_delta_time(p), philo->id, SLEEP, p));
		wait_ms(p->tt_sleep, p);
		if (p->life == 0)
			sem_wait(p->can_eat);
		add_print(p, get_print(get_delta_time(p), philo->id, THINK, p));
	}
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
	{
		while (++i < (p->nb_philos * 2))
			sem_post(p->sem_fork_sync);
	}
	else
		sem_wait(p->sem_fork_sync);
	philo_life(p, philo);
	return (NULL);
}
