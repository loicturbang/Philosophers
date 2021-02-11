/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:33:47 by user42            #+#    #+#             */
/*   Updated: 2021/02/11 11:15:44 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		add_print(t_p *p, char *str)
{
	t_list *lst;

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

	p = (t_p *)arg;
	while (p->life)
	{
		usleep(500);
		if (p->to_print)
			print_lst(p);
	}
	free_print_list(p);
	exit(0);
}
