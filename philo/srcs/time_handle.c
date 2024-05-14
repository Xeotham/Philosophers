/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:18:00 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 13:16:04 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// int	global_timer(size_t time, t_philo *philo)
// {
// 	size_t	clock;
// 	size_t	last_meal;

// 	clock = 0;
// 	last_meal = (philo->param->base_time.tv_sec * 1000000) + philo->param->base_time.tv_usec;
// 	while (clock < time)
// 	{
// 		if (clock >= philo->param->time_to_die - last_meal
// 			|| one_died(philo, philo->param))
// 		{
// 			if (!print_msg(philo, DEAD))
// 				return (0);
// 			change_state(philo, P_DEAD);
// 			return (0);
// 		}
// 		usleep(100);
// 		clock += 100;
// 	}
// 	return (1);
// }

int	global_timer(size_t time, t_philo *philo)
{
	struct timeval	clock;
	size_t			base_time;
	size_t			timer;
	size_t			last_meal;

	timer = 0;
	gettimeofday(&clock, NULL);
	base_time = (clock.tv_sec * 1000000) + clock.tv_usec;
	last_meal = (philo->param->base_time.tv_sec * 1000000) + philo->param->base_time.tv_usec;
	while (timer < time)
	{
		gettimeofday(&clock, NULL);
		timer = ((clock.tv_sec * 1000000) + clock.tv_usec) - base_time;
		if (last_meal - timer >= philo->param->time_to_die
			|| one_died(philo, philo->param))
		{
			if (!print_msg(philo, DEAD))
				return (0);
			change_state(philo, P_DEAD);
			return (0);
		}
	}
	return (1);
}

size_t	get_timestamp(struct timeval *base_clock)
{
	static struct timeval	base_time;
	struct timeval			clock;

	if (base_clock)
	{
		base_time = (*base_clock);
		printf("The clock is ready...\n");
		return (0);
	}
	else
	{
		gettimeofday(&clock, NULL);
		clock.tv_usec += ((clock.tv_sec - base_time.tv_sec) * 1000000);
		return ((clock.tv_usec - base_time.tv_usec) / 1000);
	}
}
