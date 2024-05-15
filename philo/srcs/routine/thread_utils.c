/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:16:47 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/15 10:46:22 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

size_t	everyone_ate(t_philo **philos, t_param *param)
{
	int		i;
	size_t	philo_num;


	i = 0;
	philo_num = 0;
	if (param->num_to_eat == (size_t)-1)
		return (-1);
	while (philos[i])
	{
		pthread_mutex_lock(&philos[i]->check_state);
		if (philos[i]->nb_ate >= param->num_to_eat)
			philo_num++;
		pthread_mutex_unlock(&philos[i]->check_state);
		i++;
	}
	return (philo_num);
}

void	change_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->check_state);
	if (state == P_SLEEP)
		philo->nb_ate++;
	philo->state = state;
	pthread_mutex_unlock(&philo->check_state);
}

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
