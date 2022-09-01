/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:03:18 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/01 15:56:43 by nmichael         ###   ########.fr       */
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
	const long long	timestamp = get_time() - philos->data->starting_time;

	pthread_mutex_lock(&philos->data->print_mutex);
	if (!philos->data->ph_dead && flg == 0)
		printf("%lld %d has taken a fork\n", timestamp, philos->id + 1);
	else if (!philos->data->ph_dead && flg == 1)
		printf("%lld %d is eating\n", timestamp, philos->id + 1);
	else if (!philos->data->ph_dead && flg == 2)
		printf("%lld %d is sleeping\n", timestamp, philos->id + 1);
	else if (!philos->data->ph_dead && flg == 3)
		printf("%lld %d is thinking\n", timestamp, philos->id + 1);
	else if (flg == 4)
		printf("%lld %d died\n", timestamp, philos->id + 1);
	pthread_mutex_unlock(&philos->data->print_mutex);
}

// void return_forks(t_philos *philos)
// {
	
// }

void take_one_fork(t_philos *philos)
{

	pthread_mutex_lock(philos->l_fork);
	pthread_mutex_lock(philos->r_fork);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
	// usleep(50);
}

void	take_forks(t_philos *philos)
{
 	// take_one_fork(philos);
	pthread_mutex_lock(philos->l_fork);
	pthread_mutex_lock(&philos->data->print_mutex);
	output(philos, 0);
	pthread_mutex_unlock(&philos->data->print_mutex);
	pthread_mutex_unlock(philos->l_fork);
	// take_one_fork(philos);
	pthread_mutex_lock(philos->l_fork);
	pthread_mutex_lock(&philos->data->print_mutex);
	output(philos, 0);
	pthread_mutex_unlock(&philos->data->print_mutex);
	pthread_mutex_unlock(philos->l_fork);
}
