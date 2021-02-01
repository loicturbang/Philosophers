/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:00 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 10:36:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Init date
** pthread create philos
** pthread check deaths
*/

void	*init_philo(void *arg)
{
	t_philo *philo;
	t_philo_one *p;

	philo = (t_philo *)arg;
	p = philo->p;
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&p->philos[(philo->id + 1) % p->nb_philos]->mutex);
	print_status(get_delta_time(philo), philo->id, EAT);
	set_starve_time(philo, INIT);
	printf("starve time | philo_id : %d | bef eat: %lu\n", philo->id, philo->starve_t_delta);
	wait_ms(p->tt_eat, philo);
	//init delta time
	set_starve_time(philo, DELTA);
	printf("starve time | philo_id : %d | aft eat: %lu\n", philo->id, philo->starve_t_delta);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&p->philos[(philo->id + 1) % p->nb_philos]->mutex); //avant sleep
	print_status(get_delta_time(philo), philo->id, SLEEP);
	wait_ms(p->tt_sleep, philo);
	print_status(get_delta_time(philo), philo->id, THINK);
	return (NULL);
}

void	*init_check_death(void *arg)
{
	(void)arg;
	printf("Deaths\n");
	return (NULL);
}

int		init_create_threads(t_philo_one *p)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
	{
		p->philos[i] = malloc(sizeof(t_philo));
		pthread_mutex_init(&p->philos[i]->mutex, NULL);
		p->philos[i]->p = p;
		p->philos[i]->id = i;
		get_delta_time(p->philos[i]);
		set_starve_time(p->philos[i], INIT);
	}
	i = -1;
	while (++i < p->nb_philos)
	{
		if (pthread_create(&p->philos[i]->th, NULL, &init_philo, p->philos[i]) != 0)
			return (-1);
		//usleep(19); (with 200 philos -> 9ms latence)
	}
	if (pthread_create(&p->th_death, NULL, &init_check_death, NULL) != 0)
		return (-1);
	i = -1;
	while (++i < p->nb_philos)
	{
		if (pthread_join(p->philos[i]->th, NULL) != 0)
			return (-1);
	}
	if (pthread_join(p->th_death, NULL) != 0)
		return (-1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_philo_one *p;

	if (!(argc >= 5 && argc <= 6))
		return (argument_error(ARGU_ERROR));
	p = malloc(sizeof(t_philo_one));
	if (parsing_argu(argc, argv, p) == NO_NUM_INT)
	{
		free(p);
		return (NO_NUM_INT);
	}
	p->philos = malloc(sizeof(t_philo) * p->nb_philos);
	/*
	printf("Num : %d\n", ft_count_num(1223334444));
	printf("Itoa : %s\n", ft_itoa(1223334444));
	print_status(1000, 1, SLEEP);
	*/
	init_create_threads(p);
	free(p);
	return (0);
}
