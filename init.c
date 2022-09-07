/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:32:06 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/02 11:55:16 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	allocation(t_data *data)
{
	data->philos = calloc((data->numb), sizeof(t_philos));
	data->philos->thread = calloc((data->numb), sizeof(pthread_t));
	if (!data->philos->thread)
		cleaning(data, 2);
	data->forks = calloc((data->numb), sizeof(pthread_mutex_t));
	if (!data->forks)
		cleaning(data, 2);
	// philos->data->ph_n_meal = calloc((philos->data->numb), sizeof(int));
	// if (!philos->data->ph_n_meal)
	// 	cleaning(philos, 2);
	// philos->data->ph_end = calloc((philos->data->numb), sizeof(bool));
	// if (!philos->data->ph_end)
	// 	cleaning(philos, 2);
	// philos->data->ph_n_meal = calloc((philos->data->numb), sizeof(int));
	// if (!philos->data->ph_n_meal)
	// 	cleaning(philos, 2);
	// philos->data->ph_end = calloc((philos->data->numb), sizeof(bool));
	// if (!philos->data->ph_end)
	// 	cleaning(philos, 2);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi2(t_data *data, char *str)
{
	int		i;
	long	r;

	i = 0;
	r = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' \
		|| str[i] == '\f' || str[i] == '\r')
			i++;
	while (ft_isdigit(str[i]))
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	if (ft_isdigit(str[i - 1]) == 0 || str[i] != '\0' || r > INT_MAX)
		cleaning(data, 0);
	return (r);
}

void	init(t_data *data, int argc, char **argv)
{
	int i;

	i = 0;
	data->numb = ft_atoi2(data, argv[1]);
	data->time_to_die = ft_atoi2(data, argv[2]);
	data->time_to_eat = ft_atoi2(data, argv[3]);
	data->time_to_sleep = ft_atoi2(data, argv[4]);
	if (argc == 6)
		data->six_c = ft_atoi2(data, argv[5]);
	else
		data->six_c = -1;
	allocation(data);
	data->ph_done = 0;
	data->ph_dead = false;
}
