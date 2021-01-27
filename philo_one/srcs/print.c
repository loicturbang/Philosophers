/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:26:54 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 17:14:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			print_status(unsigned long ms, int philo_id, int status)
{
	ft_putnbr_ull(ms);
	write(STDOUT_FILENO, "ms ", 3);
	ft_putnbr(philo_id);
	if (status == SLEEP)
		ft_putstr_fd(" is sleeping\n", STDOUT_FILENO);
	else if (status == EAT)
		ft_putstr_fd(" is eating\n", STDOUT_FILENO);
	else if (status == FORK)
		ft_putstr_fd(" has taken a fork\n", STDOUT_FILENO);
	else if (status == THINK)
		ft_putstr_fd(" is thinking\n", STDOUT_FILENO);
	else if (status == DEAD)
		ft_putstr_fd(" died\n", STDOUT_FILENO);
}

int				argument_error(int error)
{
	if (error == ARGU_ERROR)
	{
		ft_putstr_fd("\nBad number of arguments\nUse ", STDERR_FILENO);
		ft_putstr_fd("./philo_one [nb_philo] [tt_die]", STDERR_FILENO);
		ft_putstr_fd(" [tt_eat] [tt_sleep] (opt. nb eat)\n", STDERR_FILENO);
	}
	else if (error == NO_NUM_INT)
		ft_putstr_fd("\nError - Use only numeric characters as arguments\n", \
															STDERR_FILENO);
	return (error);
}

