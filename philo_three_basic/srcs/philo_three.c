/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:00 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 09:47:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		init_parse(t_p *p, int argc, char **argv)
{
	if (parsing_argu(argc, argv, p) == NO_NUM_INT)
	{
		free(p);
		return (NO_NUM_INT);
	}
	if ((p->must_eat_nb <= 0 && argc == 6) || p->nb_philos <= 1)
	{
		argument_error(TOO_LOW);
		free(p);
		return (TOO_LOW);
	}
	p->phil = malloc(sizeof(t_philo) * p->nb_philos);
	if (!p->phil)
	{
		free(p);
		return (ERR_MALLOC);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_p *p;

	unlink_sem_philos();
	if (!(argc >= 5 && argc <= 6))
		return (argument_error(ARGU_ERROR));
	p = malloc(sizeof(t_p));
	if (!p)
		return (ERR_MALLOC);
	if (init_parse(p, argc, argv) != 0)
		return (0);
	init_create_threads(p);
	free(p);
	unlink_sem_philos();
	return (0);
}
