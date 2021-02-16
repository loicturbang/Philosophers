/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:33:47 by user42            #+#    #+#             */
/*   Updated: 2021/02/11 13:26:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		add_print(t_p *p, char *str)
{
	t_list *lst;

	sem_wait(p->add_list);
	if (p->to_print == NULL)
	{
		p->to_print = ft_lstnew(str);
		if (!p->to_print)
			return (show_error(ERR_MALLOC));
	}
	else
	{
		lst = ft_lstnew(str);
		if (!lst)
			return (show_error(ERR_MALLOC));
		ft_lstadd_back(&p->to_print, lst);
	}
	sem_post(p->add_list);
	return (0);
}

void	print_lst(t_p *p)
{
	void	*ptr;

	ptr = p->to_print;
	sem_wait(p->print);
	write(1, "a", 1);
	while (p->to_print)
	{
		write(1, (char *)p->to_print->content, \
									ft_strlen((char *)p->to_print->content));
		p->to_print = p->to_print->next;
	}
	p->to_print = ptr;
	free_print_list(p);
	p->to_print = NULL;
	sem_post(p->print);
}

void	*init_print(void *arg)
{
	t_p		*p;
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	p = philo->p;
	sem_wait(p->sem_fork_sync);
	get_delta_time(p);
	//remove time condition and protect add list to add only elements before die
	while (p->life)
	{
		usleep(500);
		if (p->to_print)
			print_lst(p);
	}
	free_print_list(p);
	exit(0);
}
