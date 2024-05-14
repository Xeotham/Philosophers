/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:16:47 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 16:49:17 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	change_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->check_state);
	if (philo->state == P_EAT)
		philo->nb_ate++;
	philo->state = state;
	pthread_mutex_unlock(&philo->check_state);
}
