/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:58:38 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/21 20:41:04 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ==== INCLUDES ==== */

# include <errno.h>
# include <ft_printf.h>
# include <ph_error.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

/* ==== DEFINE ====*/

typedef enum e_state
{
	P_EAT,
	P_THINK,
	P_SLEEP,
	P_DEAD,
}					t_state;

# define FORK "has taken a fork."
# define EAT "is eating."
# define SLEEP "is sleeping."
# define THINK "is thinking."
# define DEAD "died."

# define LEFT_FORK 0
# define RIGHT_FORK 1

# define MAKE_CHECK 0
# define MAKE_FORK 1

/* ==== STRUCT ==== */
/*
	- av[1] = Numbers of philosophers/forks
	- av[2] = time to die (ms)
	- av[3] = time to eat (ms)
	- av[4] = time to sleep (ms)
	- av[5] = number of time each philo need to eat (optional)
*/

typedef struct s_fork
{
	int				fork_used;
	pthread_mutex_t	check_use;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_param
{
	int				nb_args;
	int				death;
	t_fork			**forks;
	size_t			philo_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_to_eat;
	struct timeval	base_time;
	struct s_philo	**philos;
	pthread_mutex_t	check_death;
}					t_param;

typedef struct s_philo
{
	int				philo_num;
	int				left_fork;
	int				right_fork;
	int				fork_use;
	size_t			nb_ate;
	t_param			*param;
	t_state			state;
	pthread_t		philo;
	struct timeval	last_meal;
	pthread_mutex_t	check_state;
}					t_philo;

/* ==== UTILS ==== */

int					ft_isdigit(int c);
size_t				ft_atou(const char *str);
size_t				philo_count(void *philo);
void				free_philo(void *philo, size_t size);
int					are_dead(t_philo **philos);
int					print_msg(t_philo *philo, char *msg);
void				free_param(t_param *param);
size_t				get_timestamp(struct timeval *base_clock);
int					global_timer(size_t time, t_philo *philo);
void				unlock_fork_mutex(t_philo *philo, t_fork **forks);
void				change_state(t_philo *philo, t_state state);
int					one_died(t_param *param);
size_t				everyone_ate(t_philo **philos, t_param *param);
t_fork	**creat_fork_tab(size_t fork_num, size_t index, t_fork **forks);


/* ==== PHILOS_HANDLE ==== */
void				philo_loop(t_philo **philos, t_param *param);
t_philo				**create_philo(t_param *param);
t_fork	**create_forks(t_param *param, t_fork **forks, int check, size_t index);
int					do_eat(t_philo *philo, t_param *param);
int					do_think(t_philo *philo);
int					do_sleep(t_philo *philo, t_param *param);
int					check_death(t_philo *philo, t_param *param);

#endif