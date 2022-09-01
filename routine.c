// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   routine.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/08/24 15:50:34 by nmichael          #+#    #+#             */
// /*   Updated: 2022/08/26 11:08:20 by nmichael         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

void	eating(t_philos *philos)
{
	take_forks(philos);
	philos->data->ph_n_meal++;
	philos->last_meal = get_time();
	pthread_mutex_lock(philos->l_fork);
	pthread_mutex_lock(philos->r_fork);
	output(philos, 1);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
	sleep_ms(philos->data->time_to_eat);
	philos->status = sleeping;
	// if (!philos->thread)
	// 	return_forks(philos, 0);
	// else
	// 	return_forks(philos, philos->id);
}

void	routine_helper(int status, t_philos *philos)
{
	if (status == sleeping)
	{
		eating(philos);
		output(philos, 2);
		philos->status = thinking;
		sleep_ms(philos->data->time_to_sleep);
		output(philos, 3);
	}
	if (status == lonely)
	{
		take_one_fork(philos);
		output(philos, 0);
		pthread_mutex_lock(&philos->data->print_mutex);
		output(philos, 4);
		pthread_mutex_unlock(&philos->data->print_mutex);
		sleep_ms(philos->data->time_to_sleep);
		philos->data->ph_dead = true;
	}
}

void	*routine(void *param)
{
	t_philos  *philos;
	int       i;

	i = 0;
	philos = param;
	while(philos->data->flag_done == 1)
		usleep(1);
	if (philos->data->numb % 2)
		sleep_ms(philos->data->time_to_die);
	while(philos->data->ph_dead == false)
	{
		if (philos->status == lonely)
			routine_helper(lonely, philos);
		if (philos->status == sleeping)
			routine_helper(sleeping, philos);
	}
    return (NULL);
}
