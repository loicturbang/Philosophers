/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:26:54 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 09:30:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char			*get_status(int status)
{
	char	*str;

	str = NULL;
	if (status == SLEEP)
		str = ft_strdup(" is sleeping\n");
	else if (status == EAT)
		str = ft_strdup(" is eating\n");
	else if (status == FORK)
		str = ft_strdup(" has taken a fork\n");
	else if (status == THINK)
		str = ft_strdup(" is thinking\n");
	else if (status == DEAD)
		str = ft_strdup(" died\n");
	if (!str)
		return (NULL);
	return (str);
}

void			print_status(unsigned long ms, int philo_id, int status)
{
	char	*str;
	char	*str2;
	char	*tmp;

	str = ft_itoa(ms);
	str2 = ft_strjoin(str, "ms ");
	free(str);
	str = ft_itoa((unsigned long)philo_id);
	tmp = ft_strjoin(str2, str);
	free(str2);
	free(str);
	str2 = get_status(status);
	str = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	write(1, str, ft_strlen(str));
	free(str);
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

void			debug(t_philo_one *philo_one)
{
	printf("Philo one :\n\n");
	printf("nb_philo: %d\n", philo_one->nb_philos);
	printf("tt_die %d\n", philo_one->tt_die);
	printf("tt_eat %d\n", philo_one->tt_eat);
	printf("tt_sleep %d\n", philo_one->tt_sleep);
	printf("nb_eat %d\n", philo_one->must_eat_nb);
}
