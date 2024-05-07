/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:20:54 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 16:46:51 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_fork	*creat_forks(t_param *param)
{
	unsigned int	i;
	t_fork			*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * param->philo_num);
	if (!forks)
		return (NULL);
	while (i < param->philo_num)
	{
		forks[i].fork_used = 0;
		pthread_mutex_init(&forks[i].check_use, NULL);
		pthread_mutex_init(&forks[i++].fork, NULL);
	}
	return (forks);
}

static t_philo	*init_philo(int i_philo, int philo_num)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_num = i_philo + 1;
	philo->right_fork = i_philo;
	if (i_philo == philo_num - 1)
		philo->left_fork = 0;
	else
		philo->left_fork = i_philo + 1;
	philo->fork_use[0] = 0;
	philo->fork_use[1] = 0;
	philo->state = P_EAT;
	gettimeofday(&philo->last_eat, NULL);
	return (philo);
}

t_philo	**creat_philo(t_param *param)
{
	unsigned int	i;
	t_philo			**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * (param->philo_num + 1));
	if (!philos)
		return (NULL);
	philos[param->philo_num] = NULL;
	while (i < param->philo_num)
	{
		philos[i] = init_philo(i, param->philo_num);
		if (!philos[i])
		{
			free_philo(philos, i);
			return (NULL);
		}
		i++;
	}
	return (philos);
}
