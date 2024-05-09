/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:32:14 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/09 22:07:17 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	check_death(t_philo *philo, t_param *param)
{
	size_t	death_timer;
	struct timeval	clock;

	if (are_dead(param->philos))
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
