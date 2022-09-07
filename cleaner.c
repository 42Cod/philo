/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:41:04 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/01 14:27:24 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_data *data)
{
	(void)data;
	// if (philos->data->forks)
	// 	free(philos->data->forks);
	// if (philos->thread)
	// 	free(philos->thread);
	// if (philos->l_fork)
	// 	free(philos->l_fork);
	// if (philos->r_fork)
	// 	free(philos->r_fork);
	// free(philos->data);
	// if (philos)
	// 	free(philos);
	exit(0);
}

void	cleaning(t_data *data, int flag)
{
	if (flag == 0)
	{
		printf(HELP);
		exit (EXIT_FAILURE);
	}
	free_mem(data);
	if (flag == 3)
	{
		printf(THERR);
		exit (EXIT_FAILURE);
	}
	if (flag == 2)
	{
		printf(MEMERR);
		exit (EXIT_FAILURE);
	}
	exit (EXIT_SUCCESS);
}
