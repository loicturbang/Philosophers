/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:26:54 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 17:29:31 by user42           ###   ########.fr       */
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

char			*get_print(unsigned long ms, int philo_id, int status, t_p *p)
{
	char	*str;
	char	*str2;
	char	*tmp;

	(void)p;
	str = ft_itoa(ms);
	str2 = ft_strjoin(str, " ");
	free(str);
	str = ft_itoa((unsigned long)(philo_id + 1));
	tmp = ft_strjoin(str2, str);
	free(str2);
	free(str);
	str2 = get_status(status);
	str = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	return (str);
}

int				argument_error(int error)
{
	if (error == ARGU_ERROR)
	{
		ft_putstr_fd("Bad number of arguments\nUse ", 2);
		ft_putstr_fd("./philo_one [nb_philo] [tt_die]", 2);
		ft_putstr_fd(" [tt_eat] [tt_sleep] (opt. nb eat)\n", 2);
	}
	else if (error == NO_NUM_INT)
		ft_putstr_fd("Error - Use only numeric characters as arguments\n", 2);
	else if (error == TOO_LOW)
		ft_putstr_fd("Error - Use only num > 1 for nb_philo | > 0 nb_eat\n", 2);
	else if (error == BAD_PHILO)
		ft_putstr_fd("Error - 200 is max number of philos\n", 2);
	else if (error == BAD_MS)
		ft_putstr_fd("Error - 60 is minimum number for ms\n", 2);
	return (error);
}

int				show_error(int error)
{
	if (error == ERR_TH_CREAT)
		ft_putstr_fd("Error: pthread_create failed\n", 2);
	else if (error == ERR_MALLOC)
		ft_putstr_fd("Error: pthread_join failed\n", 2);
	else if (error == ERR_MUTEX)
		ft_putstr_fd("Error: mutex_init failed\n", 2);
	return (error);
}
