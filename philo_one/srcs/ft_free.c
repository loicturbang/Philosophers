/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:54:50 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 18:12:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		free_back(t_p *p, int i)
{
	while (--i >= 0)
	{
		pthread_mutex_destroy(&p->phil[i]->fork);
		free(p->phil[i]);
	}
	free(p->phil);
	pthread_mutex_destroy(&p->mutex_dead);
	return (0);
}

int		ft_free(t_p *p, int ret)
{
	int i;

	i = -1;
	while (++i < p->nb_philos)
		free(p->phil[i]);
	free(p->phil);
	return (ret);
}

void	free_print_list(t_p *p)
{
	t_list *lst;

	while (p->to_print)
	{
		free(p->to_print->content);
		lst = p->to_print;
		p->to_print = p->to_print->next;
		free(lst);
	}
}
