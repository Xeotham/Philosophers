/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:32:14 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/21 15:39:48 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	one_died(t_param *param)
{
	int	death;

	death = 0;
	pthread_mutex_lock(&param->check_death);
	if (param->death == 1)
		death = 1;
	pthread_mutex_unlock(&param->check_death);
	return (death);
}

int	check_death(t_philo *philo, t_param *param)
{
	size_t			death_timer;
	struct timeval	clock;

	if (one_died(param))
		return (0);
	gettimeofday(&clock, NULL);
	clock.tv_usec += clock.tv_sec * 1000000;
	death_timer = clock.tv_usec - (philo->last_meal.tv_usec
			+ (philo->last_meal.tv_sec * 1000000));
	if (death_timer >= param->time_to_die)
	{
		change_state(philo, P_DEAD);
		return (0);
	}
	return (1);
}

int	do_think(t_philo *philo)
{
	if (!print_msg(philo, THINK))
		return (0);
	change_state(philo, P_EAT);
	return (1);
}

int	do_sleep(t_philo *philo, t_param *param)
{
	philo->fork_use = 0;
	unlock_fork_mutex(philo, param->forks);
	if (!print_msg(philo, SLEEP))
		return (0);
	gettimeofday(&philo->last_meal, NULL);
	if (!global_timer(param->time_to_sleep, philo))
		return (0);
	usleep(130);
	change_state(philo, P_THINK);
	return (1);
}
