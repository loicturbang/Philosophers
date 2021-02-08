/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 17:19:21 by user42           ###   ########.fr       */
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
	else if (type == SEM_DEATH)
	{
		philo_name = ft_strjoin("p_sem_death_", tmp);
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
	p->phil[i]->must_eat = sem_open(philo_name, O_CREAT, 0600, 0);
	free(philo_name);
	if (p->phil[i]->must_eat == SEM_FAILED)
		return (-1);
	philo_name = get_sem_name(SEM_DEATH, i);
	p->phil[i]->sem_death = sem_open(philo_name, O_CREAT, 0600, 0);
	free(philo_name);
	if (p->phil[i]->sem_death == SEM_FAILED)
		return (-1);
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
	sem_unlink("print");
	while (--i >= 0)
	{
		philo_name = get_sem_name(SEM_MUST_EAT, i);
		sem_unlink(philo_name);
		free(philo_name);
		philo_name = get_sem_name(SEM_DEATH, i);
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
