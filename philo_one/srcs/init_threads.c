/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 16:28:07 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
		if (pthread_mutex_init(&p->phil[i]->mutex, NULL) != 0)
			return (i);
		p->phil[i]->p = p;
		p->phil[i]->id = i;
		p->phil[i]->last_eat = 0;
		p->phil[i]->nb_eat = 0;
	}
	if (pthread_mutex_init(&p->mutex_dead, NULL) != 0)
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
		if (pthread_create(&p->phil[i]->th, NULL, &init_philo, p->phil[i]) != 0)
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
	int i;

	error = init_structure(p);
	if (error != -2)
	{
		if (error == -1)
			ft_free(p, MALLOC_ERROR);
		else
			free_back(p, error);
		return (-1);
	}
	if (create_threads(p) != 0)
		return (ft_free(p, 0));
	pthread_mutex_lock(&p->mutex_dead);
	pthread_mutex_lock(&p->mutex_dead);
	pthread_mutex_destroy(&p->mutex_dead);
	i = -1;
	while (++i < p->nb_philos)
		pthread_mutex_destroy(&p->phil[i]->mutex);
	ft_free(p, 0);
	return (0);
}
