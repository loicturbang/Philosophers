/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:27:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 10:26:36 by lturbang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4
# define ARGU_ERROR 1
# define NO_NUM_INT 2
# define TOO_LOW 3
# define BAD_PHILO 4
# define BAD_MS 5
# define ERR_MUTEX 2
# define ERR_TH_CREAT 3
# define ERR_MALLOC 4

/*
**	s_list
*/

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*
** s_philo
*/

typedef struct	s_philo
{
	int					status;
	int					nb_eat;
	int					id;
	int					pause;
	unsigned long		last_eat;
	pthread_t			th;
	pthread_mutex_t		fork;
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
	int				life;
	int				finish_eat;
	struct s_philo	**phil;
	pthread_t		th_death;
	pthread_mutex_t mutex_dead;
	pthread_mutex_t print;
	pthread_mutex_t dead_print;
	pthread_mutex_t sync;
	pthread_mutex_t can_eat;
	unsigned long	start_time;
	struct s_list	*to_print;
}				t_p;

/*
**		PHILO
*/

void			*monitoring(void *arg);
void			*init_philo(void *arg);
int				init_create_threads(t_p *p);

/*
**		UTILS
*/

unsigned int	ft_strlen(const char *s);
char			*ft_strdup(const char *src);
void			ft_putstr_fd(char *str, int fd);
int				ft_atoi(const char *str);
char			*ft_itoa(unsigned long num);
char			*ft_strjoin(char const *s1, char const *s2);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst);

/*
**		MUTEX UTILS
*/

int				mutex_init(t_p *p);
void			mutex_destroy(t_p *p);

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

/*
**		TIME
*/

unsigned long	get_delta_time(t_p *p);
void			wait_ms(unsigned long ms_wait, t_p *p);

#endif
