/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:32:14 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/10 15:49:53 by mhaouas          ###   ########.fr       */
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
	size_t	death_timer;
	struct timeval	clock;

	if (one_died(param))
		return (0);
	gettimeofday(&clock, NULL);
	clock.tv_usec += ((clock.tv_sec - philo->last_meal.tv_sec) * 1000000);
	death_timer = clock.tv_usec - philo->last_meal.tv_usec;
	if (death_timer >= param->time_to_die)
	{
		print_msg(philo->philo_num, DEAD);
		change_state(philo, P_DEAD);
		return (0);
	}
	return (1);
}

void	do_think(t_philo *philo)
{
	print_msg(philo->philo_num, THINK);
	change_state(philo, P_EAT);
}

int	do_sleep(t_philo *philo, t_param *param)
{
	size_t	timer;

	print_msg(philo->philo_num, SLEEP);
	timer = 0;
	if (!global_timer(param->time_to_sleep, philo))
		return (0);
	change_state(philo, P_THINK);
	return (1);
}
