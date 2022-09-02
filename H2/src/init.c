/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:50:24 by hngo              #+#    #+#             */
/*   Updated: 2022/03/10 19:02:38 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	join_threads(void)
{
	int	i;

	i = 0;
	while (i < data()->threads_num)
	{
		if (pthread_join(data()->philos[i]->id, NULL) != 0)
			errormsg("Couldn't join threads.", i);
		i++;
	}
}

t_philo	*new_philo(int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (pthread_mutex_init(&philo->lock_fork, NULL) != 0)
		errormsg("Couldn't create mutex!", i);
	if ((pthread_create(&philo->id, NULL, &routine, philo)) == 0)
		data()->threads_num++;
	else
		errormsg("Couldn't create pthread!", i);
	philo->num = i + 1;
	philo->status = waiting;
	philo->ate = 0;
	philo->fork = true;
	philo->last_meal = 0;
	return (philo);
}

void	init_philos(void)
{
	int	i;

	data()->philos = malloc(sizeof(t_philo *) * data()->input.p_num + 1);
	i = -1;
	if (!data()->philos)
		errormsg("Philos couldn't be allocated!", i);
	if (pthread_mutex_init(&data()->print, NULL) != 0)
		errormsg("Couldn't create Mutex!", i);
	if (pthread_mutex_init(&data()->init_lock, NULL) != 0)
		errormsg("Couldn't create Mutex!", i);
	pthread_mutex_lock(&data()->init_lock);
	while (++i < data()->input.p_num)
		data()->philos[i] = new_philo(i);
	if (data()->threads_num == 1)
		data()->philos[0]->status = lonely;
	data()->philos[i] = NULL;
	data()->init_routine = true;
	data()->starttime = get_time();
	pthread_mutex_unlock(&data()->init_lock);
	join_threads();
}

void	init_data(char **argv)
{
	data()->input.p_num = ft_atoi(argv[1]);
	data()->input.ttd = ft_atoi(argv[2]);
	data()->input.tte = ft_atoi(argv[3]);
	data()->input.tts = ft_atoi(argv[4]);
	if (argv[5])
		data()->input.eat = ft_atoi(argv[5]);
	else
		data()->input.eat = -1;
	data()->threads_num = 0;
	data()->printable = true;
	data()->init_routine = false;
	data()->dead = false;
	init_philos();
}
