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

// void	die(t_data *data)
// {
// 	pthread_mutex_lock(data->forks);
// 	if (get_time() - data->philos->last_meal > data->time_to_die)
// 	{
// 		data->ph_dead = true;
// 		output(data, 4);
// 	}
// 	pthread_mutex_unlock(data->forks);
// }

// void	eating(t_data *data)
// {
// 	pthread_mutex_lock(data->philos->l_fork);
// 	output(data, 0);
// 	pthread_mutex_unlock(data->philos->l_fork);
// 	pthread_mutex_lock(data->philos->r_fork);
// 	output(data, 0);
// 	pthread_mutex_unlock(data->philos->r_fork);
// 	output(data, 1);
// 	data->ph_n_meal++;
// 	data->philos->last_meal = get_time();
// 	sleep_ms(data->time_to_eat);
// 	die(data);
// 	data->philos->status = ate;
// 	// if (!philos->thread)
// 	// 	return_forks(philos, 0);
// 	// else
// 	// 	return_forks(philos, philos->id);
// }

// void	routine_helper(int status, t_data *data)
// {
// 	if (status == sleeping)
// 	{
// 		eating(data); //eating
// 		if (data->philos->status == ate)
// 		{
// 			output(data, 2); //sleeping
// 			data->philos->status = thinking;
// 		}
// 		if(data->philos->status == thinking)
// 		{
// 			output(data, 3); //thinking
// 			sleep_ms(data->time_to_sleep);
// 			data->philos->status = sleeping;
// 		}
// 	}
// 	if (status == lonely) //just one
// 	{
// 		// take_one_fork(philos);
// 		// output(philos, 0);
// 		pthread_mutex_lock(&data->print_mutex);
// 		output(data, 4);
// 		pthread_mutex_unlock(&data->print_mutex);
// 		sleep_ms(data->time_to_sleep);
// 		data->ph_dead = true;
// 	}
// }

void	checker(t_data *data)
{
	if ((get_useconds() - data->philos->last_meal) / 1000 > \
	(size_t)data->time_to_die)
	{
		data->ph_end = 1;
		output(data, 4);
	}
}

void	check_philos_death(t_data *data)
{
	int	i;

	while (!data->ph_end)
	{
		ft_usleep(2000);
		i = 0;
		while (!data->ph_end && i < data->numb)
		{
			checker(data);
			i++;
		}
	}
	return ;
}

void	eat(t_data *data)
{
	while (1)
	{
		if (philo->info->fork_status[philo->r_fork] == FREE)
		{
			pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
			philo->info->fork_status[philo->r_fork] = LOCK;
			output(data, 0);
			pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
			philo->info->fork_status[philo->l_fork] = LOCK;
			output(data, 0);
			philo->last_meal = get_useconds();
			output(data, 1);
			check_philo_must_eat(philo);
			sleep_ms(data->time_to_eat);
			philo->info->fork_status[philo->r_fork] = FREE;
			philo->info->fork_status[philo->l_fork] = FREE;
			pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
			pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
			break ;
		}
		else
			usleep(100);
	}
}
void	sleep(t_data *data)
{
	output(data, 3);
	sleep_ms(data->time_to_sleep);
	data->philos->status = sleeping;
}
void	think(t_data *data)
{
	output(data, 2);
	data->philos->status = thinking;
}

void	*routine(void *param)
{
	t_data	*data;
	int	i;

	i = 0;
	data = param;
	while(data->flag_done == 1)
		usleep(1);
	if (data->numb % 2)
		sleep_ms(data->time_to_eat - 1);
	while(data->ph_dead == false)
	{
		eat(data);
		check_philos_death(data);
		sleep(data);
		check_philos_death(data);
		think(data);
		check_philos_death(data);
	}
    return (NULL);
}
