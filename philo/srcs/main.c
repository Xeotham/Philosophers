/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:02:02 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/07 16:32:23 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/*
	- av[1] = Numbers of philosophers/forks 
	- av[2] = time to die (ms)
	- av[3] = time to eat (ms)
	- av[4] = time to sleep (ms)
	- av[5] = number of time each philo need to eat (optional)
*/

int	check_args(char **av)
{
	int	i;
	int	j;
	
	i = 0;
	while (av[++i])
	{
		if (av[i][0] == '+')
			j = 0;
		else
			j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
		}
		if (!ft_atou(av[i]) || !j || ft_atou(av[i]) * 1000 < ft_atou(av[i]))
			return (0);
	}
	return (1);
}

t_param	*store_param(int ac, char **av)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (NULL);
	memset(param, 0, sizeof(t_param));
	param->nb_args = ac;
	param->philo_num = ft_atou(av[0]);
	param->time_to_die = ft_atou(av[1]) * 1000;
	param->time_to_eat = ft_atou(av[2]) * 1000;
	param->time_to_sleep = ft_atou(av[3]) * 1000;
	if (ac == 5)
		param->num_to_eat = ft_atou(av[4]);
	return (param);
}

int	main(int ac, char **av)
{
	t_param			*param;

	if (ac < 5 || ac > 6)
		return (1); //error :wrong args
	if (!check_args(av))
		return (1); //error :wrong syntax arg
	param = store_param(ac - 1, av + 1);
	if (!param)
		return (1);
	gettimeofday(&param->base_time, NULL);
	get_timestamp(&param->base_time);
	param->philos = creat_philo(param);
	if (!param->philos)
	{
		free(param);
		return (1);
	}
	philo_loop(param);
	// int	i = -1;
	// while (philos[++i])
	// 	printf("philo number %d : L_fork %d , R_fork %d , state %d\n", i + 1, philos[i]->left_fork, philos[i]->right_fork, philos[i]->state);
	free_philo(param->philos, philo_count(param->philos));
	free(param);
}
