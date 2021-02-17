/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 13:32:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		init_structure(t_p *p)
{
	int		i;

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
	}
	if (sem_thread_init(p) != 0)
		return (-1);
	return (-2);
}

int		create_check_threads(t_p *p, int i)
{
	if (pthread_create(&p->phil[i]->th_death, NULL, &check_death, \
															p->phil[i]) != 0)
		return (show_error(ERR_TH_CREAT));
	init_philo(p->phil[i]);
	return (0);
}

int		create_threads(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
	{
		p->phil[i]->pid = fork();
		if (p->phil[i]->pid < 0)
			return (show_error(ERR_FORK));
		else if (p->phil[i]->pid == 0)
		{
			if (create_check_threads(p, i) != 0)
				return (-1);
			exit(0);
		}
		usleep(100);
	}
	return (0);
}

int		init_create_threads(t_p *p)
{
	int i;
	int error;

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
	i = -1;
	while (++i < p->nb_philos)
		sem_wait(p->sem_dead);
	sem_close(p->sem_dead);
	i = -1;
	while (++i < p->nb_philos)
		kill(p->phil[i]->pid, SIGKILL);
	i = -1;
	while (++i < p->nb_philos * 2)
		sem_post(p->forks);
	sem_close(p->forks);
	ft_free(p, 0);
	return (0);
}
