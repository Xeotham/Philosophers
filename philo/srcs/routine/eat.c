/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeo <xeo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:02:27 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/18 20:03:40 by xeo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	should_eat(t_philo *philo, t_philo *l_philo)
{
	int	eat;

	eat = 1;
	if (philo->philo_num % 2 == 0)
		pthread_mutex_lock(&philo->check_state);
	pthread_mutex_lock(&l_philo->check_state);
	if (philo->philo_num % 2 == 1)
		pthread_mutex_lock(&philo->check_state);
	if (!l_philo->just_ate)
	{
		eat = 0;
		philo->just_ate = 0;
	}
	pthread_mutex_unlock(&philo->check_state);
	pthread_mutex_unlock(&l_philo->check_state);
	return (eat);
}

static int	check_fork(t_philo *philo, t_fork *first_fork, t_fork *second_fork)
{
	pthread_mutex_lock(&first_fork->check_use);
	pthread_mutex_lock(&second_fork->check_use);
	if (!first_fork->fork_used && !second_fork->fork_used)
	{
		first_fork->fork_used = 1;
		second_fork->fork_used = 1;
		if (!print_msg(philo, FORK)
			|| !print_msg(philo, FORK))
		{
			pthread_mutex_unlock(&second_fork->check_use);
			pthread_mutex_unlock(&first_fork->check_use);
			return (0);
		}
		pthread_mutex_lock(&second_fork->fork);
		pthread_mutex_lock(&first_fork->fork);
		philo->fork_use = 1;
	}
	pthread_mutex_unlock(&second_fork->check_use);
	pthread_mutex_unlock(&first_fork->check_use);
	return (1);
}

int	do_eat(t_philo *philo, t_param *param)
{
	int		state;
	t_philo	**philos;

	philos = param->philos;
	if (!should_eat(philo, philos[philo->left_philo]))
		return (1);
	if (philo->philo_num % 2 == 0)
		state = check_fork(philo, &param->forks[philo->left_fork],
				&param->forks[philo->right_fork]);
	else
		state = check_fork(philo, &param->forks[philo->right_fork],
				&param->forks[philo->left_fork]);
	if (!state)
		return (0);
	if (philo->fork_use)
	{
		if (!print_msg(philo, EAT))
			return (0);
		if (!global_timer(param->time_to_eat, philo))
			return (0);
		change_state(philo, P_SLEEP);
	}
	return (1);
}
