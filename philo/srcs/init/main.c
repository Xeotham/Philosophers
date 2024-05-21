/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:02:02 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/21 09:30:43 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
			if (!ft_isdigit(av[i][j]) && error_handle(P_SYNTAX_ERROR, NULL,
					NULL))
				return (0);
		}
		if ((!ft_atou(av[i]) || !j || (ft_atou(av[i]) * 1000) < ft_atou(av[i]))
			&& error_handle(P_INVALID_ARGS, NULL, NULL))
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
	else
		param->num_to_eat = -1;
	pthread_mutex_init(&param->check_death, NULL);
	printf("The bowl is set on the table...\n");
	return (param);
}

t_philo	**init_all(int ac, char **av)
{
	t_param	*param;
	t_philo	**philos;

	param = store_param(ac - 1, av + 1);
	if (!param && error_handle(P_MALLOC_ERROR, NULL, NULL))
		return (NULL);
	philos = create_philo(param);
	if (!philos && error_handle(P_MALLOC_ERROR, param, NULL))
		return (NULL);
	param->philos = philos;
	param->forks = malloc(sizeof(t_fork) * param->philo_num);
	if (!param->forks && error_handle(P_MALLOC_ERROR, param, philos))
		return (NULL);
	param->forks = create_forks(param, param->forks, MAKE_CHECK, 0);
	if (!param->forks && error_handle(P_MUTEX_ERROR, param, philos))
		return (NULL);
	return (philos);
}

int	main(int ac, char **av)
{
	t_philo	**philos;
	t_param	*param;

	if (ac > 6)
		return (error_handle(P_ARGS_ERROR_1, NULL, NULL));
	else if (ac < 5)
		return (error_handle(P_ARGS_ERROR_2, NULL, NULL));
	else if (ft_atou(av[1]) <= 1)
		return (error_handle(P_SYNTAX_ERROR, NULL, NULL));
	if (!check_args(av))
		return (1);
	philos = init_all(ac, av);
	if (!philos)
		return (1);
	param = (*philos)->param;
	philo_loop(philos, param);
	return (error_handle(JUST_FREE, param, philos));
}
