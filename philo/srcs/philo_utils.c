/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:36:42 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/06 18:40:42 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <philosophers.h>

size_t	philo_count(void *philo)
{
	size_t	i;
	void	**tmp;

	i = 0;
	tmp = philo;
	while (tmp[i])
		i++;
	return (i);
}

void	free_philo(void *philo, size_t size)
{
	void	**tmp;
	size_t	i;

	i = 0;
	tmp = philo;
	while (tmp[i] && i < size)
		free(tmp[i++]);
	free(tmp);
}