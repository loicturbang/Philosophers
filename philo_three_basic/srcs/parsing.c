/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:40:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 17:37:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int			parsing_argu(int argc, char **argv, t_p *philo_one)
{
	int i;

	i = 0;
	while (argv[++i] && i < argc)
	{
		if (is_num(argv[i]) == 0)
			return (argument_error(NO_NUM_INT));
	}
	philo_one->nb_philos = ft_atoi(argv[1]);
	philo_one->tt_die = ft_atoi(argv[2]);
	philo_one->tt_eat = ft_atoi(argv[3]);
	philo_one->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_one->must_eat_nb = ft_atoi(argv[5]);
	else
		philo_one->must_eat_nb = -1;
	return (0);
}
