/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:33:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 11:02:08 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*update_must_eat(void *arg)
{
	t_p			*p;
	int			i;

	p = (t_p *)arg;
	i = -1;
	while (++i < p->nb_philos)
		sem_wait(p->must_eat);
	i = -1;
	p->life = 0;
	sem_wait(p->print); //optionnel
	while (++i < p->nb_philos)
		sem_post(p->phil[i]->sem_death);
	return (NULL);
}

void	print_death(t_p *p, t_philo *philo)
{
	int				i;
	char			*str;

	i = -1;
	sem_wait(p->sem_dead_print);
	p->life = 0;
	while (++i < p->nb_philos)
		if (i != philo->id)
			sem_post(p->phil[i]->sem_death);
	if (p->is_printing == 1)
		sem_wait(p->print); //obligé ou attendre usleep(500)
	str = get_print(get_delta_time(p), philo->id, DEAD, p);
	write(1, str, ft_strlen(str));
	free(str);
	exit(0);	
	//add_print(p, get_print(get_delta_time(p), philo->id, DEAD, p));
	sem_post(philo->sem_death);
}

void	*check_death(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	sem_wait(p->sem_fork_sync);
	get_delta_time(p);
	while (1)
	{
		if (p->life == 0 || (get_delta_time(p) - philo->last_eat) >= (unsigned long)p->tt_die)
		{
			print_death(p, philo);
			return (NULL);
		}
		usleep(5);
	}
	return (NULL);
}

void	*update_death(void *arg)
{
	t_philo		*philo;
	t_p			*p;

	philo = (t_philo *)arg;
	p = philo->p;
	sem_wait(philo->sem_death);
	p->life = 0;
	while (1)
	{
		if (p->is_printing == 0)
			exit(0);
		usleep(19);
	}
}
