/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 12:49:18 by lturbang         ###   ########.fr       */
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
	print_lst(p);
	sem_post(p->sem_dead);
	return (NULL);
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
		usleep(500); //500 working
		print_lst(p);
		if ((get_delta_time(p) - philo->last_eat) >= (unsigned long)p->tt_die)
		{
			sem_wait(p->sem_dead_print);
			add_print(p, get_print(get_delta_time(p), philo->id, DEAD, p));
			print_lst(p);
			sem_post(p->sem_dead);
			return (NULL);
		}
	}
	return (NULL);
}
