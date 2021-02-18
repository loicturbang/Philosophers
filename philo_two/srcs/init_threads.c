/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 10:51:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		init_structure(t_p *p)
{
	int i;

	i = -1;
	p->life = 1;
	p->start_time = 0;
	p->to_print = NULL;
	while (++i < p->nb_philos)
	{
		p->phil[i] = malloc(sizeof(t_philo));
		if (!p->phil[i])
		{
			show_error(ERR_MALLOC);
			return (i);
		}
		p->phil[i]->p = p;
		p->phil[i]->id = i;
		p->phil[i]->last_eat = 0;
		p->phil[i]->nb_eat = 0;
		p->phil[i]->pause = 0;
	}
	if (ft_sem_init(p) != 0)
		return (-1);
	return (-2);
}

int		create_threads(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
	{
		if (pthread_create(&p->phil[i]->th, NULL, &init_philo, \
												p->phil[i]) != 0)
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
	int	i;

	error = init_structure(p);
	if (error != -2)
	{
		if (error == -1)
			ft_free(p, ERR_MALLOC);
		else
			free_back(p, error);
		return (-1);
	}
	if (create_threads(p) != 0)
	{
		ft_free(p, 0);
		return (-1);
	}
	sem_wait(p->sem_dead);
	sem_close(p->sem_dead);
	i = -1;
	while (++i < p->nb_philos * 2)
		sem_post(p->forks);
	sem_close(p->forks);
	ft_free(p, 0);
	return (0);
}
