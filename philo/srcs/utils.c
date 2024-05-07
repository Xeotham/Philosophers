/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:14:53 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 21:25:52 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

unsigned int	ft_atou(const char *str)
{
	int				i;
	unsigned int	nbr;

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
	int	i;

	i = 0;
	while (philos[i])
	{
		if (philos[i++]->state == P_DEAD)
			return (0);
	}
	return (1);
}

void	print_msg(unsigned int timestamp, int philo, char *msg)
{
	printf("[%u ms] : philo number %d %s\n", timestamp * 1000, philo, msg);
}

void	free_param(t_param *param)
{
	unsigned int	i;

	i = 0;
	if (!param)
		return ;
	if (param->philos)
		free_philo(param->philos, philo_count(param->philos));
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
