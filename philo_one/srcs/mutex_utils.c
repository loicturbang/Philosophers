/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 09:53:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 09:54:56 by user42           ###   ########.fr       */
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
