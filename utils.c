/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:03:18 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/02 11:35:45 by nmichael         ###   ########.fr       */
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

void	output(t_data *data, int flg)
{
	const long long	timestamp = get_time() - data->starting_time;

	pthread_mutex_lock(&data->print_mutex);
	if (!data->ph_dead && flg == 0)
		printf("time: %lld | %d has taken a fork\n", timestamp, data->philos->id + 1);
	else if (!data->ph_dead && flg == 1)
		printf("time: %lld | %d is eating\n", timestamp, data->philos->id + 1);
	else if (!data->ph_dead && flg == 2)
		printf("time: %lld | %d is sleeping\n", timestamp, data->philos->id + 1);
	else if (!data->ph_dead && flg == 3)
		printf("time: %lld | %d is thinking\n", timestamp, data->philos->id + 1);
	else if (flg == 4)
		printf(RED "time: %lld | Philosopher %d died\n", timestamp, data->philos->id + 1);
	pthread_mutex_unlock(&data->print_mutex);
}

// void return_forks(t_philos *philos)
// {
	
// }

void take_one_fork(t_data *data)
{

	pthread_mutex_lock(data->forks);
	pthread_mutex_unlock(data->forks);
	usleep(50);
}

void	take_forks(t_data *data)
{
 	// take_one_fork(philos);
	pthread_mutex_lock(data->forks);
	output(data, 0);
	pthread_mutex_unlock(data->forks);
	take_one_fork(data);
	pthread_mutex_lock(data->forks);
	pthread_mutex_lock(&data->print_mutex);
	output(data, 0);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(data->forks);
}
