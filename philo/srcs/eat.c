/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:02:27 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 21:25:07 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	check_fork(t_philo *philo, t_fork *forks, int fork_type)
{
	t_fork	*actual_fork;
	int		ret;

	ret = 0;
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
		print_msg(get_timestamp(NULL), philo->philo_num, FORK);
		ret = 1;
	}
	pthread_mutex_unlock(&actual_fork->check_use);
	return (ret);
}

void	do_eat(t_philo *philo, t_param *param)
{
	philo->fork_use[LEFT_FORK] = check_fork(philo, param->forks, LEFT_FORK);
	philo->fork_use[RIGHT_FORK] = check_fork(philo, param->forks, RIGHT_FORK);
	if (philo->fork_use[LEFT_FORK] && philo->fork_use[RIGHT_FORK])
	{
		print_msg(get_timestamp(NULL), philo->philo_num, EAT);
		global_timer(param->time_to_eat);
		unlock_fork_mutex(philo, param->forks);
		gettimeofday(&philo->last_eat, NULL);
		philo->state = P_SLEEP;
	}
}
