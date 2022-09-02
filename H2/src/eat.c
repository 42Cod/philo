/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:34:54 by hngo              #+#    #+#             */
/*   Updated: 2022/03/10 19:02:42 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_one_fork(t_philo *philo, t_philo *check)
{
	bool	own_fork;

	own_fork = false;
	while (own_fork == false)
	{
		pthread_mutex_lock(&philo->lock_fork);
		if (philo->fork)
		{
			philo->fork = false;
			own_fork = true;
		}
		pthread_mutex_unlock(&philo->lock_fork);
		usleep(50);
		time_to_die(check);
	}
}

void	take_forks(t_philo *philo, int id)
{
	take_one_fork(philo, philo);
	pthread_mutex_lock(&data()->init_lock);
	printmsg(id, "has taken a fork.");
	pthread_mutex_unlock(&data()->init_lock);
	if (!data()->philos[id])
		take_one_fork(data()->philos[0], philo);
	else
		take_one_fork(data()->philos[id], philo);
	pthread_mutex_lock(&data()->init_lock);
	printmsg(id, "has taken a fork.");
	pthread_mutex_unlock(&data()->init_lock);
}

void	return_forks(t_philo *philo, int neighbour)
{
	pthread_mutex_lock(&philo->lock_fork);
	philo->fork = true;
	pthread_mutex_unlock(&philo->lock_fork);
	pthread_mutex_lock(&data()->philos[neighbour]->lock_fork);
	data()->philos[neighbour]->fork = true;
	pthread_mutex_unlock(&data()->philos[neighbour]->lock_fork);
}

void	eat(t_philo *philo)
{
	int	p_num;
	int	id;

	id = philo->num;
	p_num = data()->threads_num;
	take_forks(philo, id);
	philo->ate++;
	philo->last_meal = get_time();
	pthread_mutex_lock(&data()->init_lock);
	printmsg(id, "is eating.");
	pthread_mutex_unlock(&data()->init_lock);
	sleep_ms(philo, data()->input.tte);
	philo->status = sleeping;
	if (!data()->philos[id])
		return_forks(philo, 0);
	else
		return_forks(philo, id);
}
