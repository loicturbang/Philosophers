/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 15:47:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h> //remove
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

/*
**		UTILS
*/

unsigned int	ft_strlen(const char *s);
char			*ft_strdup(const char *src);
void			ft_putnbr_ull(unsigned long long n);
void			ft_putstr(char *str);
void			ft_putnbr(int n);

/*
**		PHILO
*/

void			print_status(unsigned long long ms, int philo_id, int status);

#endif
