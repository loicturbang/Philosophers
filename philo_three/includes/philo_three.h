/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 17:47:23 by user42           ###   ########.fr       */
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
# include <signal.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4
# define ARGU_ERROR 1
# define NO_NUM_INT 2
# define TOO_LOW 3
# define INIT 1
# define DELTA 2
# define MALLOC_ERROR 10
# define SEM_DEATH 1
# define SEM_MUST_EAT 2

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
	int					pid;
	sem_t				*must_eat;
	sem_t				*sem_death;
	struct s_p			*p;
	pthread_t			th_eat;
	pthread_t			th_death;
	pthread_t			th_u_death;
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
	struct s_philo	**phil;
	pthread_t		th_must_eat;
	sem_t			*forks;
	sem_t			*sem_dead;
	sem_t			*sem_fork_sync_philo;
	sem_t			*sem_fork_sync_death;
	sem_t			*sem_dead_print;
	sem_t			*dead_child;
	sem_t			*print;
	int				life;
}				t_p;

/*
**		PHILO
*/

void			*init_check_death(void *arg);
void			*init_philo(void *arg);
void			*update_must_eat(void *arg);
int				init_create_threads(t_p *p);
void			*update_death(void *arg);
void			*check_death(void *arg);

/*
**		SEM
*/

void			unlink_sem_philos(void);
int				create_sem_philos(t_p *p, int i);
int				sem_thead_init(t_p *p);

/*
**		UTILS
*/

unsigned int	ft_strlen(const char *s);
char			*ft_strdup(const char *src);
void			ft_putstr_fd(char *str, int fd);
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
**		FREE
*/

int				free_back(t_p *p, int i);
int				ft_free(t_p *p, int ret);

/*
**		TIME
*/

unsigned long	get_delta_time(void);
void			wait_ms(unsigned long ms_wait);

#endif
