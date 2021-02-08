/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:54:50 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 14:38:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		free_back(t_p *p, int i)
{
	while (--i >= 0)
		free(p->phil[i]);
	free(p->phil);
	sem_close(p->forks);
	sem_close(p->sem_dead);
	return (0);
}

int		ft_free(t_p *p, int ret)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
		free(p->phil[i]);
	free(p->phil);
	while (++i < p->nb_philos * 2)
		sem_post(p->forks);
	sem_close(p->forks);
	sem_close(p->sem_dead);
	return (ret);
}
