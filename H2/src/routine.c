/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:53:27 by hngo              #+#    #+#             */
/*   Updated: 2022/03/10 19:02:31 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_status(int status, t_philo *philo)
{
	if (status == sleeping)
	{
		pthread_mutex_lock(&data()->init_lock);
		printmsg(philo->num, "is sleeping.");
		pthread_mutex_unlock(&data()->init_lock);
		philo->status = thinking;
		sleep_ms(philo, data()->input.tts);
	}
	else if (status == thinking)
	{
		pthread_mutex_lock(&data()->init_lock);
		printmsg(philo->num, "is thinking.");
		pthread_mutex_unlock(&data()->init_lock);
		philo->status = waiting;
	}
	else if (status == lonely)
	{
		take_one_fork(philo, philo);
		pthread_mutex_lock(&data()->init_lock);
		printmsg(philo->num, "has taken a fork.");
		pthread_mutex_unlock(&data()->init_lock);
		sleep_ms(philo, data()->input.ttd);
		data()->dead = true;
	}
}

bool	init_routine(void)
{
	pthread_mutex_lock(&data()->init_lock);
	if (data()->init_routine == true)
	{
		pthread_mutex_unlock(&data()->init_lock);
		return (true);
	}
	pthread_mutex_unlock(&data()->init_lock);
	return (false);
}

void	*routine(void *varg)
{
	t_philo	*philo;

	philo = (t_philo *)varg;
	while (!init_routine())
		usleep(10);
	philo->last_meal = get_time();
	if (philo->num % 2)
		sleep_ms(philo, data()->input.tte);
	while (init_routine())
	{
		if (philo->status == lonely)
			philo_status(lonely, philo);
		if (data()->input.eat && philo->ate == data()->input.eat)
			break ;
		if (philo->status == sleeping)
			philo_status(sleeping, philo);
		if (philo->status == thinking)
			philo_status(thinking, philo);
		if (philo->status == waiting)
			eat(philo);
	}
	return (NULL);
}
