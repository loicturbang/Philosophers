/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 13:35:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*init_philo(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&p->philos[(philo->id + 1) % p->nb_philos]->mutex);
		print_status(get_delta_time(philo), philo->id, FORK, p);
		print_status(get_delta_time(philo), philo->id, EAT, p);
		philo->last_eat = get_delta_time(philo);
		wait_ms(p->tt_eat, philo);
		philo->nb_eat++;
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&p->philos[(philo->id + 1) % p->nb_philos]->mutex);
		print_status(get_delta_time(philo), philo->id, SLEEP, p);
		wait_ms(p->tt_sleep, philo);
		print_status(get_delta_time(philo), philo->id, THINK, p);
	}
	return (NULL);
}
