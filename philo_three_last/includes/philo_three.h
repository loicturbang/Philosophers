/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 11:18:04 by user42           ###   ########.fr       */
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
# define SEM_DEATH 1
# define ERR_FORK 1
# define ERR_SEM_OPEN 2
# define ERR_TH_CREAT 3
# define ERR_TH_JOIN 4
# define ERR_MALLOC 4

/*
**	s_list
*/

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** s_philo
*/

typedef struct	s_philo
{
	int					nb_eat;
	int					id;
	int					sem_done;
	unsigned long		last_eat;
	int					pid;
	struct s_p			*p;
	pthread_t			th_eat;
	pthread_t			th_death;
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
	sem_t			*sem_fork_sync;
	sem_t			*sem_dead_print;
	sem_t			*print;
	sem_t			*must_eat;
	sem_t			*fork_check;
	unsigned long	start_time;
	struct s_list	*to_print;
	int				life;
}				t_p;

/*
**		PHILO
*/

void			*init_check_death(void *arg);
void			*init_philo(void *arg);
void			*update_must_eat(void *arg);
int				init_create_threads(t_p *p);
void			*check_death(void *arg);

/*
**		SEM
*/

void			unlink_sem_philos(void);
int				sem_thread_init(t_p *p);

/*
**		UTILS
*/

unsigned int	ft_strlen(const char *s);
char			*ft_strdup(const char *src);
void			ft_putstr_fd(char *str, int fd);
int				ft_atoi(const char *str);
char			*ft_itoa(unsigned long num);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putnbr_ul(unsigned long n);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **alst, t_list *new);

/*
**		PARSING
*/

int				parsing_argu(int argc, char **argv, t_p *philos);

/*
**		PRINTING
*/

int				argument_error(int error);
char			*get_print(unsigned long ms, int philo_id, int status, t_p *p);
int				show_error(int error);
int				add_print(t_p *p, char *str);
void			print_lst(t_p *p);

/*
**		FREE
*/

int				free_back(t_p *p, int i);
int				ft_free(t_p *p, int ret);
void			free_print_list(t_p *p);

/*
**		TIME
*/

unsigned long	get_delta_time(t_p *p);
void			wait_ms(unsigned long ms_wait, t_p *p);

#endif
