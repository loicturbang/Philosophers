/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 11:08:42 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		check_eat_death(t_p *p, int *finish_eat, int i)
{
	if (p->must_eat_nb != -1 && (p->philos[i]->nb_eat >= p->must_eat_nb))
		(*finish_eat)++;
	if (*finish_eat == p->nb_philos)
	{
		p->life = 0;
		sem_post(p->sem_dead);
		return (1);
	}
	if ((get_delta_time(p->philos[i]) - p->philos[i]->last_eat) >= \
											(unsigned long)p->tt_die)
	{
		print_status(get_delta_time(p->philos[i]), p->philos[i]->id, DEAD, p);
		p->life = 0;
		sem_post(p->sem_dead);
		return (1);
	}
	return (0);
}

void	*init_check_death(void *arg)
{
	t_p			*p;
	int			i;
	int			finish_eat;

	p = (t_p *)arg;
	while (1)
	{
		i = -1;
		finish_eat = 0;
		while (p->philos[++i] && i < p->nb_philos)
		{
			if (check_eat_death(p, &finish_eat, i) == 1)
				return (NULL);
			usleep(19);
		}
	}
	return (NULL);
}
