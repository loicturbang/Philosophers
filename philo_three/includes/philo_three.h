/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 13:50:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4
# define ARGU_ERROR 1
# define NO_NUM_INT 2
# define ZERO_NUM 3
# define INIT 1
# define DELTA 2
# define MALLOC_ERROR 10

/*
** s_philo
*/

typedef struct	s_philo
{
	int					status;
	int					nb_eat;
	int					id;
	unsigned long		last_eat;
	struct timeval		time_start;
	struct timeval		time_actual;
	pthread_t			th;
	int					pid;
	struct s_p			*p;
}				t_philo;

/*
** s_p
** tt = time to
*/

typedef struct	s_p
{
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				must_eat_nb;
	int				nb_philos;
	struct s_philo	**philos;
	pthread_t		th_death;
	sem_t			*forks;
	sem_t			*sem_dead;
	int				life;
}				t_p;

/*
**		PHILO
*/

void			*init_check_death(void *arg);
void			*init_philo(void *arg);
int				init_create_threads(t_p *p);

/*
**		UTILS
*/

unsigned int	ft_strlen(const char *s);
char			*ft_strdup(const char *src);
void			ft_putnbr_ull(unsigned long n);
void			ft_putstr_fd(char *str, int fd);
void			ft_putnbr(int n);
int				ft_atoi(const char *str);
char			*ft_itoa(unsigned long num);
char			*ft_strjoin(char const *s1, char const *s2);

/*
**		PARSING
*/

int				parsing_argu(int argc, char **argv, t_p *philos);

/*
**		PRINTING
*/

int				argument_error(int error);
void			print_status(unsigned long ms, int philo_id, int status, \
																t_p *p);

/*
**		TIME
*/

unsigned long	get_delta_time(t_philo *philo);
void			wait_ms(unsigned long ms_wait, t_philo *p);

#endif
