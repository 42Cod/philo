/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:55:29 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/09 13:30:02 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker(t_philos *philos)
{
	if ((get_time() - philos->last_meal > philos->data->time_to_die))
	{
		philos->data->ph_end = 1;
		output(philos, 4);
		philos->data->ph_dead = true;
		exit(0);
	}
}

void	eat(t_philos *philos)
{
	pthread_mutex_lock(philos->l_fork);
	pthread_mutex_lock(philos->r_fork);
	output(philos, 0);
	output(philos, 0);
	output(philos, 1);
	philos->last_meal = get_time();
	philos->ph_n_meal++;
	philos->data->philos->status = ate;
	sleep_ms(philos->data->time_to_eat);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
	if (philos->ph_n_meal > philos->data->six_c)
		philos->status = waiting;
}

void	*routine(void *param)
{
	t_philos	*philos;
	int			i;

	philos = (t_philos *)param;
	philos->last_meal = get_time();
	i = 0;
	while (philos->data->flag_done == 1)
		usleep(1);
	if (philos->status == lonely)
	{
		pthread_mutex_lock(&philos->data->print_mutex);
		output(philos, 4);
		pthread_mutex_unlock(&philos->data->print_mutex);
		sleep_ms(philos->data->time_to_sleep);
		philos->data->ph_dead = true;
	}
	while (philos->data->ph_dead == false && philos->status != waiting)
	{
		eat(philos);
		if (philos->status != waiting)
		{
			sleepi(philos);
			think(philos);
		}
	}
	return (NULL);
}

void	*routine1(void *param)
{
	t_philos	*philos;
	int			i;

	philos = (t_philos *)param;
	philos->last_meal = get_time();
	i = 0;
	while (philos->data->flag_done == 1)
		usleep(1);
	if (philos->status == lonely)
	{
		pthread_mutex_lock(&philos->data->print_mutex);
		output(philos, 4);
		pthread_mutex_unlock(&philos->data->print_mutex);
		sleep_ms(philos->data->time_to_sleep);
		philos->data->ph_dead = true;
	}
	while (philos->data->ph_dead == false && philos->status != waiting)
	{
		think(philos);
		eat(philos);
		if (philos->status != waiting)
			sleepi(philos);
	}
	return (NULL);
}