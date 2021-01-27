/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:40:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 17:14:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			is_num(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int			parsing_argu(int argc, char **argv, t_philo_one *philos)
{
	int i;

	(void)philos;
	i = 1;
	while (argv[i] && i < argc)
	{
		if (is_num(argv[i]) == 0)
			return (argument_error(NO_NUM_INT));
		i++;
	}
	return (0);
}
