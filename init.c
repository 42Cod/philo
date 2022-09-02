/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:32:06 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/02 11:37:23 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	allocation(t_philos *philos)
{
	philos->thread = calloc((philos->data->numb), sizeof(pthread_t));
	if (!philos->thread)
		cleaning(philos, 2);
	philos->data->forks = calloc((philos->data->numb), sizeof(pthread_mutex_t));
	if (!philos->data->forks)
		cleaning(philos, 2);
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

int	ft_atoi2(t_philos *philos, char *str)
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
		cleaning(philos, 0);
	return (r);
}

void	init(t_philos *philos, int argc, char **argv)
{
	int i;

	i = 0;
	philos->data = malloc(sizeof(t_data));
	philos->data->numb = ft_atoi2(philos, argv[1]);
	printf("numbbb: %d", philos->data->numb);
	philos->data->time_to_die = ft_atoi2(philos, argv[2]);
	philos->data->time_to_eat = ft_atoi2(philos, argv[3]);
	philos->data->time_to_sleep = ft_atoi2(philos, argv[4]);
	if (argc == 6)
		philos->data->six_c = ft_atoi2(philos, argv[5]);
	else
		philos->data->six_c = -1;
	allocation(philos);
	philos->data->ph_done = 0;
	philos->data->ph_dead = false;
}
