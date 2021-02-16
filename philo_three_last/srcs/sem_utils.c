/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:37:59 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 11:43:54 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	unlink_sem_philos(void)
{
	sem_unlink("forks");
	sem_unlink("dead");
	sem_unlink("dead_print");
	sem_unlink("fork_sync");
	sem_unlink("print");
	sem_unlink("must_eat");
	sem_unlink("fork_check");
}

int		sem_thread_init(t_p *p)
{
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
	p->sem_fork_sync = sem_open("fork_sync", O_CREAT, 0600, 0);
	if (p->sem_fork_sync == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	p->must_eat = sem_open("must_eat", O_CREAT, 0600, 0);
	if (p->must_eat == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	p->fork_check = sem_open("fork_check", O_CREAT, 0600, p->nb_philos / 2);
	if (p->fork_check == SEM_FAILED)
		return (show_error(ERR_SEM_OPEN));
	return (0);
}
