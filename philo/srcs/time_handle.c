/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:18:00 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 16:24:46 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	global_timer(unsigned int time)
{
	int	i;
	int	iter;

	i = 0;
	iter = time / 10000000;
	while (i < iter)
	{
		time -= 10000000;
		usleep(10000000);
	}
	usleep(time);
}

unsigned int	get_timestamp(struct timeval *base_clock)
{
	static unsigned int	base_time;
	struct timeval		clock;

	if (base_clock)
	{
		base_time = base_clock->tv_usec;
		return (0);
	}
	else
	{
		gettimeofday(&clock, NULL);
		return ((base_time - clock.tv_usec) / 1000);
	}
}
