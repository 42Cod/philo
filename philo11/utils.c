/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:03:18 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/16 17:26:45 by nmichael         ###   ########.fr       */
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

void	output(t_philos *philos, int flg)
{
	long long timestamp;

	pthread_mutex_lock(&philos->data->print_mutex);
	timestamp = get_time() - philos->data->starting_time;
	if (!philos->data->ph_dead && flg == 0)
		printf("%lld %d has taken a fork\n",
			timestamp, philos->id + 1);
	else if (!philos->data->ph_dead && flg == 1)
		printf("%lld %d is eating\n",
			timestamp, philos->id + 1);
	else if (!philos->data->ph_dead && flg == 2)
		printf("%lld %d is sleeping\n", timestamp,
			philos->id + 1);
	else if (!philos->data->ph_dead && flg == 3)
		printf("%lld %d is thinking\n", timestamp,
			philos->id + 1);
	else if (flg == 4)
	{
		printf("%lld %d died\n",
			timestamp, philos->id + 1);
		exit(0);
	}
	pthread_mutex_unlock(&philos->data->print_mutex);
}

void	sleepi(t_philos *philos)
{
	output(philos, 2);
	if (philos->data->time_to_sleep > philos->data->time_to_die)
		sleep_ms(philos->data->time_to_die + 1);
	else if(philos->data->ph_dead != true)
		sleep_ms(philos->data->time_to_sleep);
}

void	think(t_philos *philos)
{
	output(philos, 3);
}
