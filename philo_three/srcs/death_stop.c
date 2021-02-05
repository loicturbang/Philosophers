/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 14:12:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	kill_stop(t_p *p)
{
	int i;

	i = -1;
	kill(0, SIGINT);
	while (++i < p->nb_philos)
		kill(p->philos[i]->pid, SIGINT); //needed ?
	//exit(0);
}

/*
** NEW
*/

void	*update_must_eat(void *arg)
{
	t_p			*p;
	int			i;

	p = (t_p *)arg;
	i = -1;
	while (++i < p->nb_philos)
	{
		sem_wait(p->philos[i]->must_eat);
	}
	kill_stop(p);
	sem_post(p->sem_dead);
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	if (philo->id +1 == p->nb_philos)
	{
		sem_post(p->sem_fork_sync_death);
	}
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
			p->life = 0;
			print_status(get_delta_time(), philo->id, DEAD, p);
			kill_stop(p);
			sem_post(p->sem_dead);
			return (NULL);
		}
		usleep(5);
	}
}
