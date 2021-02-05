/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 12:52:08 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	kill_stop(t_p *p)
{
	int i;

	i = -1;
	kill(0, SIGINT);
	while (++i < p->nb_philos)
		kill(p->philos[i]->pid, SIGINT);
	//exit(0);
}

int		check_eat_death(t_p *p, int *finish_eat, int i)
{
	if (p->must_eat_nb != -1 && (p->philos[i]->nb_eat >= p->must_eat_nb))
		(*finish_eat)++;
	if (*finish_eat == p->nb_philos)
	{
		p->life = 0;
		kill_stop(p);
		sem_post(p->sem_dead);
		return (1);
	}
	if ((get_delta_time() - p->philos[i]->last_eat) >= \
											(unsigned long)p->tt_die)
	{
		print_status(get_delta_time(), p->philos[i]->id, DEAD, p);
		p->life = 0;
		kill_stop(p);
		sem_post(p->sem_dead);
		return (1);
	}
	return (0);
}

void	*init_check_death(void *arg)
{
	t_p			*p;
	int			i;
	int			finish_eat;

	p = (t_p *)arg;
	while (1)
	{
		i = -1;
		finish_eat = 0;
		while (p->philos[++i] && i < p->nb_philos)
		{
			if (check_eat_death(p, &finish_eat, i) == 1)
				return (NULL);
			usleep(19);
		}
	}
	return (NULL);
}

/*
** NEW
*/

void	*update_must_eat(void *arg)
{
	t_p			*p;
	int			i;

	p = (t_p *)arg;
	i = -1;
	while (++i < p->nb_philos)
	{
		sem_wait(p->philos[i]->must_eat);
	}
	kill_stop(p);
	sem_post(p->sem_dead);
	return (NULL);
}
/*
void	*update_last_eat(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->eat);
		philo->last_eat = get_delta_time();
		usleep(5);
	}
	return (NULL);
}
*/
void	*check_death(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	if (philo->id +1 == p->nb_philos)
	{
		sem_post(p->sem_fork_sync_death);
	}
	else
	{
		sem_wait(p->sem_fork_sync_death);
		sem_post(p->sem_fork_sync_death);
	}
	get_delta_time();
	while (1)
	{
		if ((get_delta_time() - philo->last_eat) >= (unsigned long)p->tt_die)
		{
			p->life = 0;
			print_status(get_delta_time(), philo->id, DEAD, p);
			kill_stop(p);
			sem_post(p->sem_dead);
			return (NULL);
		}
		usleep(5);
	}
}

/*
void	*check_death(void *arg)
{
	t_p			*p;
	int			i;

	p = (t_p *)arg;
	while (1)
	{
		i = -1;
		while (++i < p->nb_philos)
		{
			if ((get_delta_time() - p->philos[i]->last_eat) >= (unsigned long)p->tt_die)
			{
				p->life = 0;
				print_status(get_delta_time(), p->philos[i]->id, DEAD, p);
				kill_stop(p);
				sem_post(p->sem_dead);
				return (NULL);
			}
			usleep(5);
		}
	}
	return (NULL);
}
*/
