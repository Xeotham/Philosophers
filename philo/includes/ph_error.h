/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:37:30 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/17 16:28:04 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_ERROR_H
# define PH_ERROR_H

typedef enum e_error
{
	P_ARGS_ERROR_1,
	P_ARGS_ERROR_2,
	P_SYNTAX_ERROR,
	P_INVALID_ARGS,
	P_MALLOC_ERROR,
	P_MUTEX_ERROR,
	JUST_FREE,
}		t_error;

# define TEMPLATE \
	"\nArgs should be : ./philo [Number of philosophers/forks: 2 - 200] \
[Time to die: min 60] [Time to eat: min 60] [Time to sleep: min 60] [Number of time philo should eat (optional)]"

int	error_handle(t_error error, void *param, void *philos);

#endif