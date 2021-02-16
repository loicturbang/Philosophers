/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 09:48:28 by user42           ###   ########.fr       */
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
		sem_wait(p->must_eat);
	p->life = 0;
	sem_post(p->dead_philo);
	return (NULL);
}

void	print_death(t_p *p, t_philo *philo)
{
	unsigned long	current_time;

	sem_wait(p->sem_dead_print);
	p->life = 0;
	current_time = get_delta_time(p);
	sem_wait(p->print);
	print_status(current_time, philo->id, DEAD, p);
	sem_post(p->dead_philo);
}

void	*check_death(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	sem_wait(p->sem_fork_sync);
	get_delta_time(p);
	while (1)
	{
		if ((get_delta_time(p) - philo->last_eat) >= (unsigned long)p->tt_die)
		{
			print_death(p, philo);
			return (NULL);
		}
		usleep(19);
	}
	return (NULL);
}
