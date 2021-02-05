/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 14:11:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** sem_wait -> remove 1 from semaphore (take 1 fork)
** sem_wait 2 times (2 forks)
** sem_post --> give fork back
*/

#include <stdio.h>

void	*init_philo(void *arg)
{
	t_philo		*philo;
	t_p			*p;
	

	philo = (t_philo *)arg;
	p = philo->p;
	printf("%d %d\n", philo->id + 1, p->nb_philos);
	if (philo->id + 1 == p->nb_philos)
	{
		sem_post(p->sem_fork_sync_philo);
	}
	else
	{
		sem_wait(p->sem_fork_sync_philo);
		sem_post(p->sem_fork_sync_philo);
	}
	get_delta_time();
	while (p->life)
	{
		sem_wait(p->forks);
		sem_wait(p->forks);
		print_status(get_delta_time(), philo->id, FORK, p);
		print_status(get_delta_time(), philo->id, FORK, p);
		print_status(get_delta_time(), philo->id, EAT, p);
		philo->last_eat = get_delta_time();
		wait_ms(p->tt_eat);
		philo->nb_eat++;
		if (philo->nb_eat >= p->must_eat_nb)
			sem_post(philo->must_eat);
		sem_post(p->forks);
		sem_post(p->forks);
		print_status(get_delta_time(), philo->id, SLEEP, p);
		wait_ms(p->tt_sleep);
		print_status(get_delta_time(), philo->id, THINK, p);
	}
	return (NULL);
}
