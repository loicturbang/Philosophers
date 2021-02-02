/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 18:39:39 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdio.h>

int		check_malloc_free(t_philo *philo, t_p *p, int i)
{
	if (!philo)
	{
		while (i >= 0)
		{
			free(p->philos[i]);
			i--;
		}
		free(p->philos);
		return (MALLOC_ERROR);
	}
	return (0);
}

int		init_structure(t_p *p)
{
	int i;

	i = -1;
	p->life = 1;
	while (++i < p->nb_philos)
	{
		p->philos[i] = malloc(sizeof(t_philo));
		if (check_malloc_free(p->philos[i], p, i) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		p->philos[i]->p = p;
		p->philos[i]->id = i;
		get_delta_time(p->philos[i]);
		p->philos[i]->last_eat = 0;
		p->philos[i]->nb_eat = 0;
	}
	sem_unlink("forks");
	sem_unlink("dead");
	sem_unlink("print");
	p->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, p->nb_philos);
	p->sem_dead = sem_open("dead", O_CREAT | O_EXCL, 0644, 0);
	p->sem_print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	return (0);
}

int		create_threads(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
	{
		if (pthread_create(&p->philos[i]->th, NULL, &init_philo, \
												p->philos[i]) != 0)
			return (-1);
		usleep(5);
	}
	if (pthread_create(&p->th_death, NULL, &init_check_death, p) != 0)
		return (-1);	
	return (0);
}

int		init_create_threads(t_p *p)
{
	int i;

	if (init_structure(p) != 0)
		return (-1);
	if (create_threads(p) != 0)
		return (-1);
	sem_wait(p->sem_dead);
	sem_close(p->sem_dead);
	printf("1\n");
	sem_close(p->sem_print);
	printf("2\n");
	sem_post(p->forks);
	sem_close(p->forks);
	printf("3\n");
	i = -1;
	while (++i < p->nb_philos)
		free(p->philos[i]);
	free(p->philos);
	return (0);
}
