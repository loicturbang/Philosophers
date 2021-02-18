/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 10:52:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*print_quit(t_p *p, t_philo *philo)
{
	char	*str;

	p->life = 0;
	sem_wait(p->sem_dead_print);
	str = get_print(get_delta_time(p), philo->id, DEAD, p);
	sem_wait(p->print);
	write(1, str, ft_strlen(str));
	free(str);
	ft_lstclear(&p->to_print);
	sem_post(p->sem_dead);
	return (NULL);
}

void	*print_eat_quit(t_p *p)
{
	print_lst(p);
	ft_lstclear(&p->to_print);
	sem_post(p->sem_dead);
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_p			*p;
	int			i;

	p = (t_p *)arg;
	sem_wait(p->sem_sync);
	get_delta_time(p);
	while (1)
	{
		i = -1;
		usleep(100);
		print_lst(p);
		while (p->phil[++i] && i < p->nb_philos)
		{
			if ((get_delta_time(p) - p->phil[i]->last_eat) >= \
					(unsigned long)p->tt_die && p->phil[i]->pause == 0)
				return (print_quit(p, p->phil[i]));
			usleep(19);
		}
		if (p->finish_eat >= p->nb_philos && p->must_eat_nb != -1)
			return (print_eat_quit(p));
	}
	return (NULL);
}
