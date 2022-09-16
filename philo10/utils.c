/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:03:18 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/16 17:18:17 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_ms(long long ms)
{
	long long	t1;	
	long long	t2;

	t1 = 0;
	t2 = get_time();
	while (t1 - t2 < ms)
	{
		usleep(100);
		t1 = get_time();
	}
}

long long	get_time(void)
{	
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleepi(t_philos *philos)
{
	long long timestamp;

	pthread_mutex_lock(&philos->data->print_mutex);
	timestamp = get_time() - philos->data->starting_time;
	printf("%lld %d is sleeping\n", timestamp, philos->id + 1);
	pthread_mutex_unlock(&philos->data->print_mutex);
	if (philos->data->ph_dead != true)
		sleep_ms(philos->data->time_to_sleep);
}

void	think(t_philos *philos)
{
	long long timestamp;

	pthread_mutex_lock(&philos->data->print_mutex);
	timestamp = get_time() - philos->data->starting_time;
	printf("%lld %d is thinking\n", timestamp, philos->id + 1);
	pthread_mutex_unlock(&philos->data->print_mutex);
}
