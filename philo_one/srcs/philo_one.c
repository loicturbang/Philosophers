/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:00 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 17:14:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main(int argc, char **argv)
{
	t_philo_one *philos;

	if (!(argc >= 5 && argc <= 6))
		return (argument_error(ARGU_ERROR));
	philos = malloc(sizeof(t_philo_one));
	if (parsing_argu(argc, argv, philos) != NO_NUM_INT)
		return (NO_NUM_INT);
	return (0);
}
