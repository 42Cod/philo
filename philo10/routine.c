/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:55:29 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/16 17:18:58 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker(t_philos *philos)
{
	long long timestamp;

	if ((get_time() - philos->last_meal > philos->data->time_to_die))
	{
		philos->data->ph_end = 1;
		philos->data->ph_dead = true;
		pthread_mutex_lock(&philos->data->print_mutex);
		timestamp = get_time() - philos->data->starting_time;
		printf("%lld %d died\n", timestamp, philos->id + 1);
		exit(0);
		pthread_mutex_unlock(&philos->data->print_mutex);
	}
}

void	eat(t_philos *philos)
{
	long long timestamp;
	
	pthread_mutex_lock(philos->l_fork);
	pthread_mutex_lock(&philos->data->print_mutex);
	timestamp = get_time() - philos->data->starting_time;
	printf("%lld %d has taken a fork\n", timestamp, philos->id + 1);
	pthread_mutex_unlock(&philos->data->print_mutex);
	pthread_mutex_lock(philos->r_fork);
	pthread_mutex_lock(&philos->data->print_mutex);
	timestamp = get_time() - philos->data->starting_time;
	printf("%lld %d has taken a fork\n", timestamp, philos->id + 1);
	pthread_mutex_lock(&philos->data->print_mutex);
	timestamp = get_time() - philos->data->starting_time;
	printf("%lld %d is eating\n", timestamp, philos->id + 1);
	pthread_mutex_unlock(&philos->data->print_mutex);
	philos->last_meal = get_time();
	sleep_ms(philos->data->time_to_eat);
	philos->ph_n_meal++;
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
	while (philos->data->lets_go == false)
		usleep(20);
	philos->last_meal = get_time();
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

void	*routine1(void *param)
{
	t_philos	*philos;
	int			i;

	philos = (t_philos *)param;
	i = 0;
	if (philos->status == lonely)
		helper2(philos);
	while (philos->data->lets_go == false)
	{
		if (philos->data->flag_done == true && philos->id == 1)
		{
			philos->data->starting_time = get_time();
			philos->data->lets_go = true;
		}
	}
	philos->last_meal = get_time();
	while (philos->data->ph_dead == false)
	{
		if (philos->data->six_c + 1 == philos->ph_n_meal)
			cleaning(philos->data, 1);
		sleepi(philos);
		think(philos);
		eat(philos);
	}
	return (NULL);
}
