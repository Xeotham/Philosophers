/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:36:38 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/17 16:33:23 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ph_error.h>
#include <philosophers.h>

const static char	*error_ms[] = {"Too much args", "Too few args",
		"Wrong args syntax", "Args are invalid", "Malloc_error",
		"Failed to init a mutex"};

int	error_handle(t_error error, void *param, void *philos)
{
	char	*template;
	int		i;
	
	i = 0;
	if (error == P_MALLOC_ERROR)
		template = "";
	else
		template = TEMPLATE;
	if (error != JUST_FREE && i++)
		ft_printf_fd(2, "Error : %s.%s\n", error_ms[error], template);
	if (philos)
		free_philo(philos, philo_count(philos));
	if (param)
		free_param(param);
	return (i);
}
