/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 14:38:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		init_structure(t_p *p)
{
	int i;

	i = -1;
	p->life = 1;
	while (++i < p->nb_philos)
	{
		p->phil[i] = malloc(sizeof(t_philo));
		if (!p->phil[i])
			return (i);
		p->phil[i]->p = p;
		p->phil[i]->id = i;
		p->phil[i]->last_eat = 0;
		p->phil[i]->nb_eat = 0;
	}
	sem_unlink("forks");
	sem_unlink("dead");
	p->forks = sem_open("forks", O_CREAT, 0600, p->nb_philos);
	if (p->forks == SEM_FAILED)
		return (-1);
	p->sem_dead = sem_open("dead", O_CREAT, 0600, 0);
	if (p->sem_dead == SEM_FAILED)
		return (-1);
	return (-2);
}

int		create_threads(t_p *p)
{
	int i;

	i = -1;
	get_delta_time();
	while (++i < p->nb_philos)
	{
		if (pthread_create(&p->phil[i]->th, NULL, &init_philo, \
												p->phil[i]) != 0)
			return (-1);
		usleep(5);
	}
	if (pthread_create(&p->th_death, NULL, &init_check_death, p) != 0)
		return (-1);
	return (0);
}

int		init_create_threads(t_p *p)
{
	int error;

	error = init_structure(p);
	if (error != -2)
	{
		if (error == -1)
			return (ft_free(p, MALLOC_ERROR));
		else
			return (free_back(p, error));
	}
	if (create_threads(p) != 0)
		return (ft_free(p, 0));
	sem_wait(p->sem_dead);
	return (ft_free(p, 0));
}
