/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:26:57 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/02 13:20:18 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	init_mtx_frks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			write(2, "Init mutex error\n", 18);
		}
		i++;
	}
}

static void	destroy_mtx_frks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

static void	creation(t_data *data)
{
	int	i;

	i = 0;
	data->starting_time = get_time();
	data->flag_done = 1;
	init_mtx_frks(data);
	while (i < data->numb)
	{
		data->philos[i].id = i;
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		usleep(50);
		i++;
	}
	data->flag_done = 0;
	i = 0;
	while (i <= data->numb)
	{
		pthread_join(&data->philos->thread[i], NULL);
		i++;
	}
	destroy_mtx_frks(data);
	return ;
}

void	create_philos(t_data *data)
{
	int	i;

	i = -1;
	
	if (data->numb == 1)
		data->philos->status = lonely;
	while(++i < data->numb)
	{
		data->philos[i].l_fork = calloc((data->numb), sizeof(pthread_mutex_t));
		data->philos[i].r_fork = calloc((data->numb), sizeof(pthread_mutex_t));
		if (data->numb == 1)
			data->philos[i].status = lonely;
		else
			data->philos[i].status = sleeping;
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].id = i;
		if (i == data->numb - 1)
			data->philos[i].l_fork = &data->forks[0];
		else
			data->philos[i].l_fork = &data->forks[i + 1];
		data->philos[i].r_fork = &data->forks[i];
	}
}

int main(int argc, char **argv)
{
	t_data  *data = NULL;

	if (argc == 5 || argc == 6)
	{
		data = malloc(sizeof(t_data));
		init(data, argc, argv);
		create_philos(data);
		creation(data);
		cleaning(data, 1);
	}
	cleaning(data, 0);
}
