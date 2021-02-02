/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:00 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 13:10:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_malloc_free(t_philo *philo, t_philo_one *p, int i)
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

int		init_structure(t_philo_one *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
	{
		p->philos[i] = malloc(sizeof(t_philo));
		if (check_malloc_free(p->philos[i], p, i) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		pthread_mutex_init(&p->philos[i]->mutex, NULL);
		p->philos[i]->p = p;
		p->philos[i]->id = i;
		get_delta_time(p->philos[i]);
		p->philos[i]->last_eat = 0;
		p->philos[i]->nb_eat = 0;
	}
	pthread_mutex_init(&p->mutex_dead, NULL);
	pthread_mutex_init(&p->mutex_print, NULL);
	return (0);
}

int		init_create_threads(t_philo_one *p)
{
	int i;

	if (init_structure(p) != 0)
		return (-1);
	i = -1;
	while (++i < p->nb_philos)
	{
		if (pthread_create(&p->philos[i]->th, NULL, &init_philo, \
												p->philos[i]) != 0)
			return (-1);
		usleep(5); //(with 200 philos -> 9ms latence)
	}
	if (pthread_create(&p->th_death, NULL, &init_check_death, p) != 0)
		return (-1);
	pthread_mutex_lock(&p->mutex_dead);
	pthread_mutex_lock(&p->mutex_dead);
	pthread_mutex_destroy(&p->mutex_dead);
	pthread_mutex_destroy(&p->mutex_print);
	i = -1;
	while (++i < p->nb_philos)
	{
		pthread_mutex_destroy(&p->philos[i]->mutex);
		free(p->philos[i]);
	}
	free(p->philos);
	return (0);
}

int		init_parse(t_philo_one *p, int argc, char **argv)
{
	if (parsing_argu(argc, argv, p) == NO_NUM_INT)
	{
		free(p);
		return (NO_NUM_INT);
	}
	if (p->must_eat_nb == 0 || p->nb_philos == 0)
	{
		argument_error(ZERO_NUM);
		return (ZERO_NUM);
	}
	p->philos = malloc(sizeof(t_philo) * p->nb_philos);
	if (!p->philos)
	{
		free(p);
		return (MALLOC_ERROR);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_philo_one *p;

	if (!(argc >= 5 && argc <= 6))
		return (argument_error(ARGU_ERROR));
	p = malloc(sizeof(t_philo_one));
	if (!p)
		return (MALLOC_ERROR);
	if (init_parse(p, argc, argv) != 0)
		return (0);
	init_create_threads(p);
	free(p);
	return (0);
}
