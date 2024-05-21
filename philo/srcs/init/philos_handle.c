/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:20:54 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/21 09:23:23 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_fork	*create_forks(t_param *param, t_fork *forks, int check, size_t index)
{
	t_fork			*tmp;
	pthread_mutex_t	*mutex;

	mutex = NULL;
	if (index == param->philo_num - 1)
		return (forks);
	if (forks && check == MAKE_CHECK)
		mutex = &forks[index].check_use;
	else if (forks && check == MAKE_FORK)
		mutex = &forks[index].fork;
	if (pthread_mutex_init(mutex, NULL))
		return (NULL);
	forks[index].fork_used = 0;
	tmp = create_forks(param, forks, !check, index + 1);
	if (!tmp)
		pthread_mutex_destroy(mutex);
	return (tmp);
}

static t_philo	*init_philo(int i_philo, int philo_num, t_param *param)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_num = i_philo;
	if (i_philo == philo_num - 1)
		philo->left_fork = 0;
	else
		philo->left_fork = i_philo + 1;
	philo->right_fork = i_philo;
	if (i_philo % 2 == 1)
		philo->just_ate = 1;
	philo->fork_use = 0;
	philo->state = P_THINK;
	philo->param = param;
	pthread_mutex_init(&philo->check_state, NULL);
	return (philo);
}

t_philo	**create_philo(t_param *param)
{
	size_t	i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * (param->philo_num + 1));
	if (!philos)
		return (NULL);
	philos[param->philo_num] = NULL;
	while (i < param->philo_num)
	{
		philos[i] = init_philo(i, param->philo_num, param);
		if (!philos[i])
		{
			free_philo(philos, i);
			return (NULL);
		}
		i++;
	}
	printf("Sits are set...\n");
	return (philos);
}
