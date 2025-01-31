/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:00 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 09:49:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_parse(t_p *p, int argc, char **argv)
{
	int error;

	error = 0;
	if (parsing_argu(argc, argv, p) == NO_NUM_INT)
		error = NO_NUM_INT;
	if ((p->must_eat_nb <= 0 && argc == 6) || p->nb_philos <= 1)
		error = TOO_LOW;
	if (p->nb_philos > 200)
		error = BAD_PHILO;
	if (p->tt_die < 60 || p->tt_eat < 60 || p->tt_sleep < 60)
		error = BAD_MS;
	if (error != 0)
	{
		free(p);
		return (argument_error(error));
	}
	p->phil = malloc(sizeof(t_philo) * p->nb_philos);
	if (!p->phil)
	{
		free(p);
		return (show_error(ERR_MALLOC));
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_p *p;

	if (!(argc >= 5 && argc <= 6))
		return (argument_error(ARGU_ERROR));
	p = malloc(sizeof(t_p));
	if (!p)
		return (show_error(ERR_MALLOC));
	if (init_parse(p, argc, argv) != 0)
		return (0);
	init_create_threads(p);
	free(p);
	return (0);
}
