/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:00 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 10:31:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Init date
** pthread create philos
** pthread check deaths
*/

void	*init_philo(void *arg)
{
	t_philo_one *p;

	p = (t_philo_one *)arg;
	pthread_mutex_lock(&p->philos[p->id].mutex);
	pthread_mutex_lock(&p->philos[p->id + 1 % p->nb_philos].mutex);
	printf("Je mange\n");
	usleep(1000000);
	pthread_mutex_unlock(&p->philos[p->id].mutex);
	pthread_mutex_unlock(&p->philos[p->id + 1 % p->nb_philos].mutex); //avant sleep
	return (NULL);
}

void	*init_check_death(void *arg)
{
	(void)arg;
	printf("Deaths\n");
	return (NULL);
}

int		init_create_threads(t_philo_one *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
	{
		p->id = i;
		pthread_mutex_init(&p->philos[i].mutex, NULL);
		if (pthread_create(&p->philos[i].th, NULL, &init_philo, p) != 0)
			return (-1);
	}
	if (pthread_create(&p->th_death, NULL, &init_check_death, NULL) != 0)
		return (-1);
	i = -1;
	while (++i < p->nb_philos)
	{
		if (pthread_join(p->philos[i].th, NULL) != 0)
			return (-1);
	}
	if (pthread_join(p->th_death, NULL) != 0)
		return (-1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_philo_one *p;

	if (!(argc >= 5 && argc <= 6))
		return (argument_error(ARGU_ERROR));
	p = malloc(sizeof(t_philo_one));
	if (parsing_argu(argc, argv, p) == NO_NUM_INT)
	{
		free(p);
		return (NO_NUM_INT);
	}
	p->philos = malloc(sizeof(t_philo) * p->nb_philos);
	init_create_threads(p);
	free(p);
	return (0);
}
