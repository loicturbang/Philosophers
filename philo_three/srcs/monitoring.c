/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 13:59:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*print_quit(t_p *p, t_philo *philo)
{
	char	*str;
	int		i;

	p->life = 0;
	sem_wait(p->sem_dead_print);
	str = get_print(get_delta_time(p), philo->id, DEAD, p);
	sem_wait(p->print);
	write(1, str, ft_strlen(str));
	free(str);
	i = -1;
	free_print_list(p);
	while (++i < p->nb_philos)
		sem_post(p->sem_dead);
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	sem_wait(p->sem_fork_sync);
	get_delta_time(p);
	while (1)
	{
		usleep(100);
		print_lst(p);
		if ((get_delta_time(p) - philo->last_eat) >= (unsigned long)p->tt_die)
			print_quit(p, philo);
		if (philo->nb_eat >= p->must_eat_nb && p->must_eat_nb != -1)
		{
			print_lst(p);
			free_print_list(p);
			sem_post(p->sem_dead);
			return (NULL);
		}
	}
	return (NULL);
}
