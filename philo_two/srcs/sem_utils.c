/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:36:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 17:34:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_sem_unlink(void)
{
	sem_unlink("forks");
	sem_unlink("dead");
	sem_unlink("print");
	sem_unlink("dead_print");
	sem_unlink("fork_sync");
	sem_unlink("fork_check");
	sem_unlink("can_eat");
}

int		ft_sem_init(t_p *p)
{
	ft_sem_unlink();
	p->forks = sem_open("forks", O_CREAT, 0600, p->nb_philos);
	if (p->forks == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	p->sem_dead = sem_open("dead", O_CREAT, 0600, 0);
	if (p->sem_dead == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	p->print = sem_open("print", O_CREAT, 0600, 1);
	if (p->print == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	p->sem_dead_print = sem_open("dead_print", O_CREAT, 0600, 1);
	if (p->sem_dead_print == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	p->sem_sync = sem_open("fork_sync", O_CREAT, 0600, 0);
	if (p->sem_sync == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	p->fork_check = sem_open("fork_check", O_CREAT, 0600, p->nb_philos / 2);
	if (p->fork_check == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	p->can_eat = sem_open("can_eat", O_CREAT, 0600, 0);
	if (p->can_eat == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	return (0);
}
