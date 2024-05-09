/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:02:27 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/09 22:04:31 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	check_fork(t_philo *philo, t_fork *forks, int fork_type, int search)
{
	t_fork	*actual_fork;
	int		ret;

	ret = 0;
	if (fork_type == RIGHT_FORK)
		actual_fork = &forks[philo->right_fork];
	else
		actual_fork = &forks[philo->left_fork];
	pthread_mutex_lock(&actual_fork->check_use);
	if (!actual_fork->fork_used)
	{
		if (search)
			return (1);
		else if (!search && check_fork(philo, forks, RIGHT_FORK, 1))
		{
			philo->fork_use[RIGHT_FORK] = 1;
			philo->fork_use[LEFT_FORK] = 1;
			forks[philo->left_fork].fork_used = 1;
			forks[philo->right_fork].fork_used = 1;
			print_msg(philo->philo_num, FORK);
			print_msg(philo->philo_num, FORK);
			pthread_mutex_lock(&forks[philo->left_fork].fork);
			pthread_mutex_lock(&forks[philo->right_fork].fork);
			ret = 1;
		}
		pthread_mutex_unlock(&forks[philo->right_fork].check_use);
	}
	if (fork_type == RIGHT_FORK && !actual_fork->fork_used)
		pthread_mutex_unlock(&actual_fork->check_use);
	pthread_mutex_unlock(&forks[philo->left_fork].check_use);
	return (ret);
}

int	do_eat(t_philo *philo, t_param *param)
{
	check_fork(philo, param->forks, LEFT_FORK, 0);
	if (philo->fork_use[LEFT_FORK] && philo->fork_use[RIGHT_FORK])
	{
		print_msg(philo->philo_num, EAT);
		if (!global_timer(param->time_to_eat, philo))
			return (0);
		unlock_fork_mutex(philo, param->forks);
		philo->fork_use[LEFT_FORK] = 0;
		philo->fork_use[RIGHT_FORK] = 0;
		gettimeofday(&philo->last_meal, NULL);
		change_state(philo, P_SLEEP);
	}
	return (1);
}
