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

void	die(t_philos *philos)
{
	pthread_mutex_lock(philos->data->forks);
	if (get_time() - philos->last_meal > philos->data->time_to_die)
	{
		philos->data->ph_dead = true;
		output(philos, 4);
	}
	pthread_mutex_unlock(philos->data->forks);
}

void	eating(t_philos *philos)
{
	pthread_mutex_lock(philos->l_fork);
	output(philos, 0);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_lock(philos->r_fork);
	output(philos, 0);
	pthread_mutex_unlock(philos->r_fork);
	output(philos, 1);
	philos->data->ph_n_meal++;
	philos->last_meal = get_time();
	sleep_ms(philos->data->time_to_eat);
	philos->status = sleeping;
	die(philos);
	// if (!philos->thread)
	// 	return_forks(philos, 0);
	// else
	// 	return_forks(philos, philos->id);
}

void	routine_helper(int status, t_philos *philos)
{
	if (status == sleeping)
	{
		eating(philos); //eating
		output(philos, 2); //sleeping
		philos->status = thinking;
		output(philos, 3); //thinking
		sleep_ms(philos->data->time_to_sleep);
		philos->status = sleeping;
	}
	if (status == lonely) //just one
	{
		// take_one_fork(philos);
		// output(philos, 0);
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
		// printf("hahah\n");
		if (philos->status == lonely)
			routine_helper(lonely, philos);
		if (philos->status == sleeping)
			routine_helper(sleeping, philos);
	}
    return (NULL);
}
