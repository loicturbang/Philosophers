/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 17:52:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*update_must_eat(void *arg)
{
	t_p			*p;
	int			i;

	p = (t_p *)arg;
	i = -1;
	while (++i < p->nb_philos)
		sem_wait(p->phil[i]->must_eat);
	i = -1;
	sem_wait(p->print);
	while (++i < p->nb_philos)
		sem_post(p->phil[i]->sem_death);
	sem_post(p->sem_dead);
	return (NULL);
}

void	check_death2(t_p *p, t_philo *philo)
{
	int i;

	i = -1;
	sem_wait(p->sem_dead_print);
	sem_wait(p->print);
	while (++i < p->nb_philos)
		if (i != philo->id)
			sem_post(p->phil[i]->sem_death);
	print_status(get_delta_time(), philo->id, DEAD, p);
	sem_post(p->sem_dead);
	sem_post(philo->sem_death);
}

void	*check_death(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	if (philo->id + 1 == p->nb_philos)
		sem_post(p->sem_fork_sync_death);
	else
	{
		sem_wait(p->sem_fork_sync_death);
		sem_post(p->sem_fork_sync_death);
	}
	get_delta_time();
	while (1)
	{
		if ((get_delta_time() - philo->last_eat) >= (unsigned long)p->tt_die)
		{
			check_death2(p, philo);
			return (NULL);
		}
		usleep(5);
	}
	return (NULL);
}

void	*update_death(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	sem_wait(philo->sem_death);
	p->life = 0;
	exit(0);
}
