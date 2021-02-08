/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 17:38:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_malloc_free(t_philo *philo, t_p *p, int i)
{
	if (!philo)
	{
		while (i >= 0)
		{
			free(p->phil[i]);
			i--;
		}
		free(p->phil);
		return (MALLOC_ERROR);
	}
	return (0);
}

int		init_structure(t_p *p)
{
	int		i;

	i = -1;
	p->life = 1;
	while (++i < p->nb_philos)
	{
		p->phil[i] = malloc(sizeof(t_philo));
		if (check_malloc_free(p->phil[i], p, i) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		p->phil[i]->p = p;
		p->phil[i]->id = i;
		p->phil[i]->last_eat = 0;
		p->phil[i]->nb_eat = 0;
		if (create_sem_philos(p, i) == -1)
			return (i);
	}
	p->forks = sem_open("forks", O_CREAT, 0600, p->nb_philos);
	if (p->forks == SEM_FAILED)
		return (-1);
	p->sem_dead = sem_open("dead", O_CREAT, 0600, 0);
	if (p->sem_dead == SEM_FAILED)
		return (-1);
	p->print = sem_open("print", O_CREAT, 0600, 1);
	if (p->print == SEM_FAILED)
		return (-1);
	p->sem_dead_print = sem_open("dead_print", O_CREAT, 0600, 1);
	if (p->sem_dead_print == SEM_FAILED)
		return (-1);
	p->sem_fork_sync_philo = sem_open("fork_sync_philo", O_CREAT, 0600, 0);
	if (p->sem_fork_sync_philo == SEM_FAILED)
		return (-1);
	p->sem_fork_sync_death = sem_open("fork_sync_death", O_CREAT, 0600, 0);
	if (p->sem_fork_sync_death == SEM_FAILED)
		return (-1);
	return (-2);
}

int		create_threads(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos && p->life)
	{
		p->phil[i]->pid = fork();
		if (p->phil[i]->pid < 0)
			return (-1);
		else if (p->phil[i]->pid == 0)
		{
			if (pthread_create(&p->phil[i]->th_eat, NULL, &init_philo, p->phil[i]) != 0)
				return (-1);
			if (pthread_create(&p->phil[i]->th_death, NULL, &check_death, p->phil[i]) != 0)
				return (-1);
			if (pthread_create(&p->phil[i]->th_u_death, NULL, &update_death, p->phil[i]) != 0)
				return (-1);
			if (pthread_join(p->phil[i]->th_death, NULL) != 0)
				return (-1);
			if (pthread_join(p->phil[i]->th_u_death, NULL) != 0)
				return (-1);
			if (pthread_join(p->phil[i]->th_eat, NULL) != 0)
				return (-1);
			exit(0);
		}
		usleep(5);
	}
	if (p->must_eat_nb != -1)
		if (pthread_create(&p->th_must_eat, NULL, &update_must_eat, p) != 0)
			return (-1);
	i = -1;
	while (++i < p->nb_philos && p->life)
		waitpid(p->phil[i]->pid, 0, 0);
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
			ft_free(p, MALLOC_ERROR);
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
