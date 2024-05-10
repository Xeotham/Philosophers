/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:19:59 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/10 16:39:24 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	unlock_fork_mutex(t_philo *philo, t_fork *forks)
{
	pthread_mutex_lock(&forks[philo->left_fork].check_use);
	if (forks[philo->left_fork].fork_used == 1)
	{
		forks[philo->left_fork].fork_used = 0;
		pthread_mutex_unlock(&forks[philo->left_fork].fork);
	}
	pthread_mutex_unlock(&forks[philo->left_fork].check_use);
	pthread_mutex_lock(&forks[philo->right_fork].check_use);
	if (forks[philo->right_fork].fork_used == 1)
	{
		pthread_mutex_unlock(&forks[philo->right_fork].fork);
		forks[philo->right_fork].fork_used = 0;
	}
	pthread_mutex_unlock(&forks[philo->right_fork].check_use);
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	t_param			*param;

	philo = ptr;
	param = philo->param;
	print_msg(philo->philo_num, JOIN);
	while (1)
	{
		if (!check_death(philo, param))
			break ;
		if (philo->state == P_EAT && !do_eat(philo, param))
			break ;
		else if (philo->state == P_SLEEP && !do_sleep(philo, param))
			break;
		else if (philo->state == P_THINK)
			do_think(philo);
	}
	if (philo->fork_use)
	{
		pthread_mutex_unlock(&param->forks[philo->left_fork].fork);
		pthread_mutex_unlock(&param->forks[philo->right_fork].fork);
	}
	if (param->philos[philo->philo_num])
		pthread_join(param->philos[philo->philo_num]->philo, NULL);
	return (NULL);
}

void	philo_loop(t_philo **philos, t_param *param)
{
	int	i;
	
	i = -1;
	while (philos[++i])
		pthread_create(&philos[i]->philo, NULL, routine, philos[i]);
	while (1)
	{
		if (are_dead(philos))
		{
			pthread_mutex_lock(&param->check_death);
			param->death = 1;
			pthread_mutex_unlock(&param->check_death);
			break ;
		}
	}
	pthread_join(philos[0]->philo, NULL);
	free_philo(philos, philo_count(philos));
}