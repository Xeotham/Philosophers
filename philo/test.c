/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:55:41 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/06 19:06:33 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	struct timeval	test;

	gettimeofday(&test, NULL);
	printf("time : hour : %ld, minutes : %ld, secondes : %ld\n", (test.tv_sec / 120) / 24, test.tv_sec / 60, test.tv_sec);
	usleep(1000000);
	gettimeofday(&test, NULL);
	printf("time : %ld", test.tv_sec);
}