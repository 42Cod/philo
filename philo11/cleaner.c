/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:41:04 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/16 14:55:37 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_data *data)
{
	(void)data;
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

void	helper1(t_data *data)
{
	int	i;

	i = 0;
	while (data->ph_dead == false && data->numb > 1)
	{
		if (data->six_c + 1 == data->philos->ph_n_meal)
			cleaning(data, 1);
		if (data->flag_done == true)
			checker(&data->philos[i]);
		i++;
		if (i >= data->numb)
			i = 0;
		//usleep(300);
	}
	i = 0;
	while (i <= data->numb)
	{
		pthread_join(&data->philos->thread[i], NULL);
		i++;
	}
	destroy_mtx_frks(data);
}

void	helper2(t_philos *philos)
{
	philos->data->starting_time = get_time();
	pthread_mutex_lock(philos->l_fork);
	pthread_mutex_unlock(philos->l_fork);
	output(philos, 0);
	sleep_ms(philos->data->time_to_die);
	philos->data->ph_dead = true;
	checker(philos);
	output(philos, 4);
	exit(0);
}
