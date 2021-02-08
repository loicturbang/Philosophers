/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:37:59 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 17:46:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int		sem_thead_init(t_p *p)
{
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
	return (0);
}
