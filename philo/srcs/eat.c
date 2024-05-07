/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:02:27 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 16:23:55 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	check_fork(t_philo *philo, t_fork *forks, int fork_type, t_param *param)
{
	t_fork	*actual_fork;

	if (fork_type == LEFT_FORK)
		actual_fork = &forks[philo->left_fork];
	else
		actual_fork = &forks[philo->right_fork];
	if (philo->fork_use[fork_type])
		return (1);
	pthread_mutex_lock(&actual_fork->check_use);
	if (!actual_fork->fork_used)
	{
		actual_fork->fork_used = 1;
		pthread_mutex_lock(&actual_fork->fork);
		pthread_mutex_unlock(&actual_fork->check_use);
		print_msg(get_timestamp(NULL), param->i_philo, FORK);
		return (1);
	}
	else
		return (0);
}

void	do_eat(t_philo *philo, t_param *param)
{
	philo->fork_use[LEFT_FORK] = check_fork(philo, param->forks, LEFT_FORK,
			param);
	philo->fork_use[RIGHT_FORK] = check_fork(philo, param->forks, RIGHT_FORK,
			param);
	if (philo->fork_use[LEFT_FORK] && philo->fork_use[RIGHT_FORK])
	{
		print_msg(get_timestamp(NULL), param->i_philo, EAT);
		global_timer(param->time_to_eat);
		gettimeofday(&philo->last_eat, NULL);
		unlock_fork_mutex(philo, param->forks);
		philo->state = P_SLEEP;
	}
}
