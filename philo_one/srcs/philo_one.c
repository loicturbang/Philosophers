/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:00 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 09:47:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main(int argc, char **argv)
{
	t_philo_one *philo_one;

	if (!(argc >= 5 && argc <= 6))
		return (argument_error(ARGU_ERROR));
	philo_one = malloc(sizeof(t_philo_one));
	if (parsing_argu(argc, argv, philo_one) == NO_NUM_INT)
		return (NO_NUM_INT);
	debug(philo_one);
	free(philo_one);
	return (0);
}
