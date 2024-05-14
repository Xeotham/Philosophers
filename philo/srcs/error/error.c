/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:36:38 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 14:39:20 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <ph_error.h>

const static char	*error_ms[] = {"Too much args", "Too few args",\
	"Wrong args syntax", "Args are invalid", "Malloc_error"};
	
void	error_handle(t_error error, void *param, void *philos)
{
	char	*template;
	t_param	*tmp_param;
	t_philo	**tmp_philos;

	tmp_philos = philos;
	tmp_param = param;
	if (error == P_MALLOC_ERROR)
		template = "";
	else
		template = TEMPLATE;
	ft_printf_fd(2, "Error : %s.%s\n", error_ms[error], template);
	if (tmp_philos)
		free_philo(tmp_philos, philo_count(tmp_philos));
	if (param)
		free_param(tmp_param);
}
