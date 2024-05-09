/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:18:00 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/09 22:07:17 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	global_timer(size_t time, t_philo *philo)
{
	size_t	timer;

	timer = 0;
	while (timer < time)
	{
		if (timer >= philo->param->time_to_die)
		{
			print_msg(philo->philo_num, DEAD);
			philo->state = P_DEAD;
			return (0);
		}
		usleep(1000);
		timer += 1000;
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
