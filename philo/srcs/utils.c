/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:14:53 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/16 17:33:56 by mhaouas          ###   ########.fr       */
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
	int				i;
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
	t_state	state;

	i = 0;
	while (philos[i])
	{
		pthread_mutex_lock(&philos[i]->check_state);
		state = philos[i]->state;
		pthread_mutex_unlock(&philos[i]->check_state);
		if (state == P_DEAD)
			return (1);
		i++;
	}
	return (0);
}

int	print_msg(t_philo *philo, char *msg)
{
	if (one_died(philo, philo->param))
		return (0);
	printf("[%zu ms] : philo number %d %s\n", get_timestamp(NULL), philo->philo_num + 1, msg);
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
		while (i < param->philo_num)
		{
			pthread_mutex_destroy(&param->forks[i].check_use);
			pthread_mutex_destroy(&param->forks[i++].fork);
		}
		free(param->forks);
	}
	free(param);
}
