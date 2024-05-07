/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:19:59 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 16:49:58 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	unlock_fork_mutex(t_philo *philo, t_fork *forks)
{
	pthread_mutex_unlock(&forks[philo->left_fork].fork);
	pthread_mutex_unlock(&forks[philo->right_fork].fork);
}

void	*routine(void *ptr)
{
	t_param			*param;
	t_philo			*philo;

	param = ptr;
	philo = param->philos[param->i_philo];
	printf("philo number %d created\n", philo->philo_num);
	while (!is_dead(philo))
	{
		if (!check_death(philo, param))
		{
			param->philos[param->i_philo]->state = P_DEAD;
			return (NULL);
		}
		if (philo->state == P_EAT)
			do_eat(philo, param);
		else if (philo->state == P_SLEEP)
			do_sleep(philo, param);
		else if (philo->state == P_THINK)
			do_think(philo, param);
	}
	return (NULL);
}

void	philo_loop(t_param *param)
{
	param->i_philo = 0;
	while (param->philos[param->i_philo])
	{
		pthread_create(&param->philos[param->i_philo]->philo, NULL, routine, param);
		param->i_philo++;
	}
}