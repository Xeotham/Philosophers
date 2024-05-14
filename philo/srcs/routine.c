/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:19:59 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 13:22:20 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// void	*is_everyone_ready(void *ptr)
// {
// 	t_philo	**philos;
// 	t_param	*param;
// 	size_t	i;
// 	size_t	philo_ready;

// 	philos = ptr;
// 	param = (*philos)->param;
// 	philo_ready = 0;
// 	while(philos[philo_ready])
// 	{
// 		i = philo_ready;
// 		pthread_mutex_lock(&philos[i]->check_state);
// 		if (philos[i]->is_ready == 1)
// 			philo_ready++;
// 		pthread_mutex_unlock(&philos[i]->check_state);
// 	}
// 	gettimeofday(&param->base_time, NULL);
// 	get_timestamp(&param->base_time);
// 	return (NULL);
// }

void	unlock_fork_mutex(t_philo *philo, t_fork *forks)
{
	pthread_mutex_unlock(&forks[philo->right_fork].fork);
	pthread_mutex_unlock(&forks[philo->left_fork].fork);
	pthread_mutex_lock(&forks[philo->left_fork].check_use);
	forks[philo->left_fork].fork_used = 0;
	pthread_mutex_unlock(&forks[philo->left_fork].check_use);
	pthread_mutex_lock(&forks[philo->right_fork].check_use);
	forks[philo->right_fork].fork_used = 0;
	pthread_mutex_unlock(&forks[philo->right_fork].check_use);
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	t_param			*param;

	philo = ptr;
	param = philo->param;
	gettimeofday(&philo->last_meal, NULL);
	print_msg(philo, JOIN);
	while (1)
	{
		if (!check_death(philo, param))
			break ;
		if (philo->state == P_EAT && !do_eat(philo, param))
			break ;
		else if (philo->state == P_SLEEP && !do_sleep(philo, param))
			break;
		else if (philo->state == P_THINK && !do_think(philo))
			break;
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
