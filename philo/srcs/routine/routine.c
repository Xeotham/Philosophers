/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:19:59 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/21 15:39:02 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	routine_loop(t_philo *philo, t_param *param)
{
	while (1)
	{
		if (!check_death(philo, param))
			return ;
		if (philo->state == P_EAT && !do_eat(philo, param))
			return ;
		else if (philo->state == P_SLEEP && !do_sleep(philo, param))
			return ;
		else if (philo->state == P_THINK && !do_think(philo))
			return ;
	}
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_param	*param;

	philo = ptr;
	param = philo->param;
	if (philo->philo_num % 2 == 1)
		usleep(130);
	gettimeofday(&philo->last_meal, NULL);
	routine_loop(philo, param);
	if (philo->fork_use)
	{
		pthread_mutex_unlock(&param->forks[philo->right_fork].fork);
		pthread_mutex_unlock(&param->forks[philo->left_fork].fork);
	}
	if (param->philos[philo->philo_num + 1])
		pthread_join(param->philos[philo->philo_num + 1]->philo, NULL);
	return (NULL);
}

void	check_philo_loop(t_philo **philos, t_param *param)
{
	while (1)
	{
		if (are_dead(philos) || (param->num_to_eat != (size_t) - 1
				&& everyone_ate(philos, param) == param->philo_num))
		{
			pthread_mutex_lock(&param->check_death);
			param->death = 1;
			pthread_mutex_unlock(&param->check_death);
			return ;
		}
	}
}

void	philo_loop(t_philo **philos, t_param *param)
{
	size_t	i;

	i = -1;
	gettimeofday(&param->base_time, NULL);
	get_timestamp(&param->base_time);
	while (++i < param->philo_num)
		pthread_create(&philos[i]->philo, NULL, routine, philos[i]);
	check_philo_loop(philos, param);
	pthread_join(philos[0]->philo, NULL);
}
