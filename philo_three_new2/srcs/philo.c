/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 14:24:23 by lturbang         ###   ########.fr       */
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
		if (p->life == 0)
			break ;
		sem_wait(p->print);
		p->is_printing = 1;
		if (p->life)
		{
			print_status(get_delta_time(p), philo->id, FORK, p);
			print_status(get_delta_time(p), philo->id, FORK, p);
			print_status(get_delta_time(p), philo->id, EAT, p);
		}
		sem_post(p->print);
		p->is_printing = 0;
		if (philo->nb_eat >= p->must_eat_nb - 1 && p->must_eat_nb != -1 && \
													philo->sem_done == 0)
		{
			philo->sem_done = 1;
			sem_post(p->must_eat);
		}
		philo->nb_eat++;
		philo->last_eat = get_delta_time(p);
		if (p->life == 0)
			break ;
		wait_ms(p->tt_eat, p);
		sem_post(p->forks);
		sem_post(p->forks);
		sem_post(p->fork_check);
		if (p->life)
			sem_wait(p->print);
		p->is_printing = 1;
		if (p->life)
			print_status(get_delta_time(p), philo->id, SLEEP, p);
		sem_post(p->print);
		p->is_printing = 0;
		if (p->life == 0)
			break ;
		wait_ms(p->tt_sleep, p);
		if (p->life)
			sem_wait(p->print);
		p->is_printing = 1;
		if (p->life)
			print_status(get_delta_time(p), philo->id, THINK, p);
		sem_post(p->print);
		p->is_printing = 0;
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
	while (++i < (p->nb_philos * 2))
		sem_post(p->sem_fork_sync);
	else
		sem_wait(p->sem_fork_sync);
	philo_life(p, philo);
	return (NULL);
}
