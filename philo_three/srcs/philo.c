/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 12:41:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** sem_wait -> remove 1 from semaphore (take 1 fork)
** sem_wait 2 times (2 forks)
** sem_post --> give fork back
*/

void	*init_philo(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	while (p->life)
	{
		sem_wait(p->forks);
		sem_wait(p->forks);
		print_status(get_delta_time(philo), philo->id, FORK, p);
		print_status(get_delta_time(philo), philo->id, FORK, p);
		print_status(get_delta_time(philo), philo->id, EAT, p);
		philo->last_eat = get_delta_time(philo);
		wait_ms(p->tt_eat, philo);
		philo->nb_eat++;
		sem_post(p->forks);
		sem_post(p->forks);
		print_status(get_delta_time(philo), philo->id, SLEEP, p);
		wait_ms(p->tt_sleep, philo);
		print_status(get_delta_time(philo), philo->id, THINK, p);
	}
	return (NULL);
}
