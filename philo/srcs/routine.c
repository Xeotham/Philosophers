/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:19:59 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 21:36:34 by mhaouas          ###   ########.fr       */
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
	t_philo			*philo;
	t_param			*param;

	philo = ptr;
	param = philo->param;
	print_msg(get_timestamp(NULL), philo->philo_num, JOIN);
	while (!is_dead(philo))
	{
		if (!check_death(philo, param))
		{
			philo->state = P_DEAD;
			return (NULL);
		}
		if (philo->state == P_EAT)
			do_eat(philo, param);
		else if (philo->state == P_SLEEP)
			do_sleep(philo, param);
		else if (philo->state == P_THINK)
			do_think(philo);
	}
	if (param->philos[philo->philo_num])
		pthread_join(param->philos[philo->philo_num]->philo, NULL);
	printf("exiting...\n");
	return (NULL);
}

void	philo_loop(t_philo **philos)
{
	int	i;
	
	i = -1;
	while (philos[++i])
		pthread_create(&philos[i]->philo, NULL, routine, philos[i]);
	pthread_join(philos[0]->philo, NULL);
}