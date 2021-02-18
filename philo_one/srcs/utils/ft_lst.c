/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:27:11 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 09:12:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_list		*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *temp;

	if (alst && new)
	{
		temp = ft_lstlast(*alst);
		if (temp)
			temp->next = new;
		else
			*alst = new;
	}
}

t_list		*ft_lstnew(void *content)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void		ft_lstdelone(t_list *lst)
{
	if (lst)
	{
		free(lst->content);
		free(lst);
	}
}

void		ft_lstclear(t_list **lst)
{
	t_list *temp;
	t_list *next;

	temp = *lst;
	if (lst)
	{
		while (temp)
		{
			next = temp->next;
			ft_lstdelone(temp);
			temp = next;
		}
		*lst = NULL;
	}
}
