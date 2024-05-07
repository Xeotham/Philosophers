/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:32:14 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 20:27:59 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	is_dead(t_philo *philo)
{
	if (philo->state == P_DEAD)
		return (1);
	return (0);
}

int	check_death(t_philo *philo, t_param *param)
{
	unsigned int	death_timer;
	struct timeval	clock;

	gettimeofday(&clock, NULL);
	death_timer = clock.tv_usec - philo->last_eat.tv_usec;
	if (death_timer >= param->time_to_die)
	{
		print_msg(get_timestamp(NULL), philo->philo_num, DEAD);
		philo->state = P_DEAD;
		return (0);
	}
	return (1);
}

void	do_think(t_philo *philo)
{
	print_msg(get_timestamp(NULL), philo->philo_num, THINK);
	philo->state = P_EAT;
}

void	do_sleep(t_philo *philo, t_param *param)
{
	struct timeval	clock;
	struct timeval	sub_clock;

	print_msg(get_timestamp(NULL), philo->philo_num, SLEEP);
	gettimeofday(&clock, NULL);
	gettimeofday(&sub_clock, NULL);
	while (sub_clock.tv_usec < (clock.tv_usec + param->time_to_sleep))
	{
		if (!check_death(philo, param))
			return ;
		gettimeofday(&sub_clock, NULL);
	}
	philo->state = P_THINK;
}
