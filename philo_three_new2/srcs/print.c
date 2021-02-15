/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:26:54 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 12:28:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

void			print_status(unsigned long ms, int philo_id, int status, t_p *p)
{
	char	*str;
	char	*str2;
	char	*tmp;

	(void)p;
	str = ft_itoa(ms);
	str2 = ft_strjoin(str, "ms ");
	free(str);
	str = ft_itoa((unsigned long)(philo_id + 1));
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

/*
char			*get_status(int status)
{
	if (status == SLEEP)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (status == EAT)
		ft_putstr_fd(" is eating\n", 1);
	else if (status == FORK)
		ft_putstr_fd(" has taken a fork\n", 1);
	else if (status == THINK)
		ft_putstr_fd(" is thinking\n", 1);
	else if (status == DEAD)
		ft_putstr_fd(" died\n", 1);
	return (NULL); //remove
}

void			print_status(unsigned long ms, int philo_id, int status, \
															t_p *p)
{
	if (p->life || status == DEAD)
	{
		if (status != DEAD)
			sem_wait(p->print);
		ft_putnbr_ul(ms);
		ft_putstr_fd(" ", 1);
		ft_putnbr_ul((unsigned long)(philo_id + 1));
		get_status(status);
		if (status != DEAD)
			sem_post(p->print);
	}
}
*/

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
	else if (error == TOO_LOW)
		ft_putstr_fd("\nError - Use only num > 0 for nb_philo & nb_eat\n", \
															STDERR_FILENO);
	return (error);
}

int				show_error(int error)
{
	if (error == ERR_FORK)
		ft_putstr_fd("Error: fork failed\n", STDERR_FILENO);
	else if (error == ERR_SEM_OPEN)
		ft_putstr_fd("Error: sem_open failed\n", STDERR_FILENO);
	else if (error == ERR_TH_CREAT)
		ft_putstr_fd("Error: pthread_create failed\n", STDERR_FILENO);
	else if (error == ERR_TH_JOIN)
		ft_putstr_fd("Error: pthread_join failed\n", STDERR_FILENO);
	else if (error == ERR_MALLOC)
		ft_putstr_fd("Error: pthread_join failed\n", STDERR_FILENO);
	return (error);
}
