/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:18:00 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/21 20:38:27 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	global_timer(size_t time, t_philo *philo)
{
	struct timeval	clock;
	size_t			base_time;
	size_t			timer;
	size_t			last_meal;

	timer = 0;
	gettimeofday(&clock, NULL);
	base_time = (clock.tv_sec * 1000000) + (clock.tv_usec);
	last_meal = base_time - ((philo->last_meal.tv_sec * 1000000) + \
	(philo->last_meal.tv_usec));
	while (timer < time)
	{
		if (last_meal + timer >= philo->param->time_to_die
			|| one_died(philo->param))
		{
			change_state(philo, P_DEAD);
			return (0);
		}
		usleep(100);
		gettimeofday(&clock, NULL);
		timer = ((clock.tv_sec * 1000000) + clock.tv_usec) - base_time;
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
		base_time.tv_sec = base_time.tv_sec * 1000;
		base_time.tv_sec += (base_time.tv_usec / 1000);
		return (0);
	}
	else
	{
		gettimeofday(&clock, NULL);
		clock.tv_sec = clock.tv_sec * 1000;
		clock.tv_sec += (clock.tv_usec / 1000);
		return ((clock.tv_sec - base_time.tv_sec));
	}
}
