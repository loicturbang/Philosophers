/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:33:47 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 09:27:53 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	t_list	**ptr;

	pthread_mutex_lock(&p->print);
	ptr = &p->to_print;
	while (p->to_print)
	{
		write(1, (char *)p->to_print->content, \
									ft_strlen((char *)p->to_print->content));
		p->to_print = p->to_print->next;
	}
	p->to_print = *ptr;
	ft_lstclear(&p->to_print);
	pthread_mutex_unlock(&p->print);
}
