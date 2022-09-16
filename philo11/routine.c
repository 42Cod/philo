/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:55:29 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/16 14:47:05 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker(t_philos *philos)
{
	if (philos->last_meal == -1 && (philos->data->time_to_eat > philos->data->time_to_die || philos->data->time_to_sleep > philos->data->time_to_die
		|| philos->data->time_to_eat + philos->data->time_to_sleep > philos->data->time_to_die))
	{
		philos->data->ph_end = 1;
		philos->data->ph_dead = true;
		sleep_ms(philos->data->time_to_die);
		output(philos, 4);
	}
	else if ((get_time() - philos->data->starting_time - philos->last_meal > philos->data->time_to_die) && philos->last_meal != -1)
	{
		philos->data->ph_end = 1;
		philos->data->ph_dead = true;
		output(philos, 4);
	}
}

void	eat(t_philos *philos)
{
	pthread_mutex_lock(philos->l_fork);
	output(philos, 0);
	pthread_mutex_lock(philos->r_fork);
	output(philos, 0);
	output(philos, 1);
	philos->last_meal = get_time() - philos->data->starting_time;
	sleep_ms(philos->data->time_to_eat);
	philos->ph_n_meal++;
	philos->data->philos->status = ate;
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}

void	*routine(void *param)
{
	t_philos	*philos;
	int			i;

	philos = (t_philos *)param;
	i = 0;
	if (philos->status == lonely)
		helper2(philos);
	philos->data->starting_time = get_time();
	//while (philos->data->flag_done == false)
	//	usleep(20);
	if (philos->id % 2)
		usleep(philos->data->time_to_eat - 1);
	philos->last_meal = -1;
	// philos->last_meal = get_time();
	while (philos->data->ph_dead == false)
	{
		eat(philos);
		sleepi(philos);
		think(philos);
	}
	if (philos->data->six_c + 1 == philos->ph_n_meal)
		cleaning(philos->data, 1);
	return (NULL);
}

