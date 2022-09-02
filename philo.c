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

static void	creation(t_data *data)
{
	int	i;

	i = 0;
	data->starting_time = get_time();
	data->flag_done = 1;
	pthread_mutex_init(data->forks, NULL);
	while (i < data->numb)
	{
		data->philos[i]->id = i;
		pthread_create(&data->philos[i]->thread, NULL, &routine, data->philos[i]);
		usleep(100);
		i++;
	}
	data->flag_done = 0;
	i = 0;
	while (i <= philos->data->numb)
	{
		pthread_join(philos->thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(philos->data->forks);
	return ;
}

void	create_philos(t_philos *philos)// alles ändern von structure, philos immer mit i
{
	int	i;

	i = - 1;
	
	if (philos->data->numb == 1)
		philos->status = lonely;
	philos->l_fork = calloc((philos->data->numb), sizeof(pthread_mutex_t)); //while allocaten jede gabel
	philos->r_fork = calloc((philos->data->numb), sizeof(pthread_mutex_t));
	while(++i < philos->data->numb)
	{
		if (philos->data->numb == 1)
			philos->status = lonely;
		else
			philos->status = sleeping;
		pthread_mutex_init(&data->forks[i], NULL);
		philos[i].id = i;
		if (i == philos->data->numb - 1)
			philos[i].l_fork = &philos->data->forks[0];
		else
			philos[i].l_fork = &philos->data->forks[i + 1];
		philos[i].r_fork = &philos->data->forks[i];
	}
}

int main(int argc, char **argv)
{
	t_philos  *philos = NULL;

	if (argc == 5 || argc == 6)
	{
		philos = malloc(sizeof(t_philos));
		init(philos, argc, argv);
		create_philos(philos);
		creation(philos);
		cleaning(philos, 1);
	}
	cleaning(philos, 0);
}
