/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 10:54:59 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_malloc_free(t_philo *philo, t_p *p, int i)
{
	if (!philo)
	{
		while (i >= 0)
		{
			free(p->philos[i]);
			i--;
		}
		free(p->philos);
		return (MALLOC_ERROR);
	}
	return (0);
}

char	*get_sem_name(int type, int i)
{
	char	*philo_name;
	char	*tmp;

	tmp = ft_itoa((unsigned long)i);
	if (type == SEM_MUST_EAT)
	{
		philo_name = ft_strjoin("p_must_eat_", tmp);
		free(tmp);
		return (philo_name);
	}
	free(tmp);
	return (NULL);
}

int		create_sem_philos(t_p *p, int i)
{
	char	*philo_name;

	philo_name = get_sem_name(SEM_MUST_EAT, i);
	p->philos[i]->must_eat = sem_open(philo_name, O_CREAT, 0600, 0); //check sem open value
	free(philo_name);
	return (0);
}

void	unlink_sem_philos(void)
{
	int		i;
	char	*philo_name;

	i = 202;
	sem_unlink("forks");
	sem_unlink("dead");
	sem_unlink("dead_print");
	sem_unlink("fork_sync_philo");
	sem_unlink("fork_sync_death");
	while (--i >= 0)
	{
		philo_name = get_sem_name(SEM_MUST_EAT, i);
		sem_unlink(philo_name);
		free(philo_name);
	}
}

int		init_structure(t_p *p)
{
	int		i;

	i = -1;
	p->life = 1;
	while (++i < p->nb_philos)
	{
		p->philos[i] = malloc(sizeof(t_philo));
		if (check_malloc_free(p->philos[i], p, i) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		p->philos[i]->p = p;
		p->philos[i]->id = i;
		p->philos[i]->last_eat = 0;
		p->philos[i]->nb_eat = 0;
		create_sem_philos(p, i);
	}
	p->forks = sem_open("forks", O_CREAT, 0600, p->nb_philos);
	p->sem_dead = sem_open("dead", O_CREAT, 0600, 0);
	p->sem_dead_print = sem_open("dead_print", O_CREAT, 0600, 1);
	p->sem_fork_sync_philo = sem_open("fork_sync_philo", O_CREAT, 0600, 0);
	p->sem_fork_sync_death = sem_open("fork_sync_death", O_CREAT, 0600, 0);	
	return (0);
}

#include <stdio.h>

int		create_threads(t_p *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos && p->life)
	{
		p->philos[i]->pid = fork();
		if (p->philos[i]->pid < 0)
			return (-1);
		else if (p->philos[i]->pid == 0)
		{
			if (pthread_create(&p->philos[i]->th_eat, NULL, &init_philo, p->philos[i]) != 0)
				return (-1);
			if (pthread_create(&p->philos[i]->th_death, NULL, &check_death, p->philos[i]) != 0)
				return (-1);
			pthread_join(p->philos[i]->th_death, NULL);
			pthread_join(p->philos[i]->th_eat, NULL);
			exit(0);
		}
		usleep(5);
	}
	i = -1;
	while (++i < p->nb_philos && p->life)
		waitpid(p->philos[i]->pid, 0 , 0);
	if (p->must_eat_nb != -1)
		if (pthread_create(&p->th_must_eat, NULL, &update_must_eat, p) != 0)
			return (-1);
	return (0);
}

int		init_create_threads(t_p *p)
{
	int i;

	if (init_structure(p) != 0)
		return (-1);
	if (create_threads(p) != 0)
		return (-1);
	sem_wait(p->sem_dead);
	sem_close(p->sem_dead);
	i = -1;
	while (++i < p->nb_philos * 2)
		sem_post(p->forks);
	sem_close(p->forks);
	i = -1;
	while (++i < p->nb_philos)
		free(p->philos[i]);
	free(p->philos);
	return (0);
}
