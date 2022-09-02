/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:27:25 by hngo              #+#    #+#             */
/*   Updated: 2022/03/10 19:02:27 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

time_t	get_time(void)
{
	struct timeval	time;
	time_t			stamp;

	gettimeofday(&time, NULL);
	stamp = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (stamp);
}

void	sleep_ms(t_philo *philo, time_t val)
{
	time_t	time;

	time = get_time();
	while (1)
	{
		if (time + val <= get_time())
			break ;
		time_to_die(philo);
		usleep(100);
	}
}

void	time_to_die(t_philo *philo)
{
	pthread_mutex_lock(&data()->init_lock);
	if (get_time() - philo->last_meal > data()->input.ttd)
	{
		data()->dead = true;
		printmsg(philo->num, "is dead.");
		data()->printable = false;
		data()->init_routine = false;
	}
	pthread_mutex_unlock(&data()->init_lock);
}
