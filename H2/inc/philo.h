/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:35:37 by hngo              #+#    #+#             */
/*   Updated: 2022/03/10 19:03:18 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

enum e_status {
	thinking = 0,
	sleeping = 1,
	waiting = 2,
	lonely = 3
};

typedef struct s_philo
{
	pthread_t		id;
	pthread_mutex_t	lock_fork;
	time_t			last_meal;
	bool			fork;
	int				num;
	int				status;
	int				ate;
}	t_philo;

typedef struct s_input
{
	int				p_num;
	time_t			ttd;
	time_t			tte;
	time_t			tts;
	int				eat;
}	t_input;

typedef struct s_data
{
	pthread_mutex_t	print;
	pthread_mutex_t	init_lock;
	pthread_mutex_t	status_lock;
	t_philo			**philos;
	t_input			input;
	int				threads_num;
	bool			printable;
	bool			init_routine;
	bool			dead;
	time_t			starttime;
}	t_data;

t_data	*data(void);
void	init_data(char **argv);
void	*routine(void *varg);
time_t	get_time(void);
void	sleep_ms(t_philo *philo, time_t val);
void	time_to_die(t_philo *philo);
void	eat(t_philo *philo);
void	take_one_fork(t_philo *philo, t_philo *check);
void	printmsg(int id, char *str);
void	errormsg(char *str, int i);
int		ft_atoi(const char *str);
void	wait_ms(time_t val);

#endif
