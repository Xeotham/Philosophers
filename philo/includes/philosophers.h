/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:58:38 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 21:35:50 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ==== INCLUDES ==== */

# include <errno.h>
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

# define JOIN "joined the table..."
# define FORK "has taken a fork."
# define EAT "is eating."
# define SLEEP "is sleeping."
# define THINK "is thinking."
# define DEAD "died."

# define LEFT_FORK 0
# define RIGHT_FORK 1

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
	unsigned int	philo_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_to_eat;
	t_fork			*forks;
	struct s_philo	**philos;
	struct timeval	base_time;
}					t_param;

typedef struct s_philo
{
	int				philo_num;
	int				left_fork;
	int				right_fork;
	int				fork_use[2];
	t_state			state;
	pthread_t		philo;
	struct timeval	last_eat;
	t_param			*param;
}					t_philo;

/* ==== UTILS ==== */

int					ft_isdigit(int c);
unsigned int		ft_atou(const char *str);
size_t				philo_count(void *philo);
void				free_philo(void *philo, size_t size);
int					is_dead(t_philo *philo);
int					are_dead(t_philo **philos);
void				print_msg(unsigned int timestamp, int philo, char *msg);
void				free_param(t_param *param);
unsigned int		get_timestamp(struct timeval *base_clock);
void				global_timer(unsigned int time);
void				unlock_fork_mutex(t_philo *philo, t_fork *forks);

/* ==== PHILOS_HANDLE ==== */
void				philo_loop(t_philo **philos);
t_philo				**creat_philo(t_param *param);
t_fork				*creat_forks(t_param *param);
void				do_eat(t_philo *philo, t_param *param);
void				do_think(t_philo *philo);
void				do_sleep(t_philo *philo, t_param *param);
int					check_death(t_philo *philo, t_param *param);

#endif