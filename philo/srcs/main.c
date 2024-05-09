/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:02:02 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/09 22:16:10 by mhaouas          ###   ########.fr       */
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
		if (!ft_atou(av[i]) || !j || (ft_atou(av[i]) * 1000) < ft_atou(av[i]))
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
	printf("The bowl is set on the table...\n");
	return (param);
}

t_philo	**init_all(int ac, char **av)
{
	t_param	*param;
	t_philo	**philos;

	param = store_param(ac - 1, av + 1);
	if (!param)
		return (NULL);
	gettimeofday(&param->base_time, NULL);
	get_timestamp(&param->base_time);
	philos = creat_philo(param);
	param->philos = philos;
	if (!philos)
	{
		free(param);
		return (NULL);
	}
	param->forks = creat_forks(param);
	if (!param->forks)
	{
		free_param(param);
		free_philo(philos, philo_count(philos));
		return (NULL);
	}
	return (philos);
}

int	main(int ac, char **av)
{
	t_philo	**philos;

	if (ac < 5 || ac > 6)
		return (1); //error :wrong args
	if (!check_args(av))
		return (1); //error :wrong syntax arg
	philos = init_all(ac, av);
	if (!philos)
		return (1);
	philo_loop(philos, (*philos)->param);
	free_param((*philos)->param);
}
