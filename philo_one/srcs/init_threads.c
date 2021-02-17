/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 18:09:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	mutex_destroy(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
	{
		pthread_mutex_destroy(&p->phil[i]->fork);
	}
	pthread_mutex_destroy(&p->mutex_dead);
	pthread_mutex_destroy(&p->print);
	pthread_mutex_destroy(&p->sync);
	pthread_mutex_destroy(&p->can_eat);
	pthread_mutex_destroy(&p->dead_print);
}

int		mutex_init(t_p *p)
{
	int error;

	error = 0;
	if (pthread_mutex_init(&p->mutex_dead, NULL) != 0)
		error = ERR_MUTEX;
	pthread_mutex_lock(&p->mutex_dead);
	if (pthread_mutex_init(&p->print, NULL) != 0)
		error = ERR_MUTEX;
	if (pthread_mutex_init(&p->sync, NULL) != 0)
		error = ERR_MUTEX;
	pthread_mutex_lock(&p->sync);
	if (pthread_mutex_init(&p->can_eat, NULL) != 0)
		error = ERR_MUTEX;
	pthread_mutex_lock(&p->can_eat);
	if (pthread_mutex_init(&p->dead_print, NULL) != 0)
		error = ERR_MUTEX;
	if (error == ERR_MUTEX)
		show_error(ERR_MUTEX);
	return (error);
}

int		init_structure(t_p *p)
{
	int i;

	i = -1;
	p->life = 1;
	while (++i < p->nb_philos)
	{
		p->phil[i] = malloc(sizeof(t_philo));
		if (!p->phil[i])
		{
			show_error(ERR_MALLOC);
			return (i);
		}
		if (pthread_mutex_init(&p->phil[i]->fork, NULL) != 0)
		{
			show_error(ERR_MUTEX);
			return (i);
		}
		p->phil[i]->p = p;
		p->phil[i]->id = i;
		p->phil[i]->last_eat = 0;
		p->phil[i]->nb_eat = 0;
	}
	if (mutex_init(p) != 0)
		return (-1);
	return (-2);
}

int		create_threads(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
	{
		if (pthread_create(&p->phil[i]->th, NULL, &init_philo, p->phil[i]) != 0)
			return (show_error(ERR_TH_CREAT));
		usleep(19);
	}
	if (pthread_create(&p->th_death, NULL, &monitoring, p) != 0)
		return (show_error(ERR_TH_CREAT));
	return (0);
}

int		init_create_threads(t_p *p)
{
	int error;

	error = init_structure(p);
	if (error != -2)
	{
		if (error == -1)
		{
			mutex_destroy(p);
			ft_free(p, ERR_MALLOC);
		}
		else
			free_back(p, error);
		return (-1);
	}
	if (create_threads(p) != 0)
		return (ft_free(p, 0));
	pthread_mutex_lock(&p->mutex_dead);
	mutex_destroy(p);
	ft_free(p, 0);
	return (0);
}
