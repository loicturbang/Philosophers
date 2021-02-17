/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 18:08:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*print_quit(t_p *p, t_philo *philo)
{
	char	*str;

	p->life = 0;
	pthread_mutex_lock(&p->dead_print);
	str = get_print(get_delta_time(p), philo->id, DEAD, p);
	pthread_mutex_lock(&p->print);
	write(1, str, ft_strlen(str));
	free(str);
	free_print_list(p);
	pthread_mutex_unlock(&p->mutex_dead);
	return (NULL);
}

void	*print_eat_quit(t_p *p)
{
	print_lst(p);
	free_print_list(p);
	pthread_mutex_unlock(&p->mutex_dead);
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_p		*p;
	int		i;

	p = (t_p *)arg;
	pthread_mutex_lock(&p->sync);
	pthread_mutex_unlock(&p->sync);
	get_delta_time(p);
	while (1)
	{
		i = -1;
		usleep(100);
		print_lst(p);
		while (p->phil[++i] && i < p->nb_philos)
		{
			if ((get_delta_time(p) - p->phil[i]->last_eat) >= \
											(unsigned long)p->tt_die)
				return (print_quit(p, p->phil[i]));
			usleep(19);
		}
		if (p->finish_eat >= p->must_eat_nb && p->must_eat_nb != -1)
			return (print_eat_quit(p));
	}
	return (NULL);
}
