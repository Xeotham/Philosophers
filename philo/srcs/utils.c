/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:14:53 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/21 20:07:18 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

size_t	ft_atou(const char *str)
{
	int		i;
	size_t	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
			i++;
		if (str[i] == '+')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			nbr = nbr * 10 + (str[i] - '0');
			i++;
		}
		return (nbr);
	}
	return (0);
}

int	are_dead(t_philo **philos)
{
	int		i;
	t_param	*param;

	i = 0;
	param = (*philos)->param;
	while (philos[i])
	{
		pthread_mutex_lock(&philos[i]->check_state);
		if (philos[i]->state == P_DEAD)
		{
			pthread_mutex_lock(&param->check_death);
			param->death = 1;
			pthread_mutex_unlock(&param->check_death);
			print_msg(philos[i], DEAD);
			pthread_mutex_unlock(&philos[i]->check_state);
			return (1);
		}
		pthread_mutex_unlock(&philos[i]->check_state);
		i++;
	}
	return (0);
}

int	print_msg(t_philo *philo, char *msg)
{
	t_param	*param;

	param = philo->param;
	pthread_mutex_lock(&param->check_death);
	if (param->death && philo->state != P_DEAD)
	{
		pthread_mutex_unlock(&param->check_death);
		return (0);
	}
	printf("[%zu ms]: Philo number %d %s\n",
		get_timestamp(NULL), philo->philo_num + 1, msg);
	pthread_mutex_unlock(&param->check_death);
	return (1);
}

void	free_param(t_param *param)
{
	size_t	i;

	i = 0;
	if (!param)
		return ;
	if (param->forks)
	{
		while (param->forks[i])
		{
			pthread_mutex_destroy(&param->forks[i]->check_use);
			pthread_mutex_destroy(&param->forks[i++]->fork);
		}
		free(param->forks);
	}
	free(param);
}
