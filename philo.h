/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:28:13 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/02 10:24:33 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FORK	"%lld %d has taken a fork\n"
# define EAT	"%lld %d is eating\n"
# define SLEEP	"%lld %d is sleeping\n"
# define THINK	"%lld %d is thinking\n"
# define DEAD	"%lld %d died\n"
# define GOAL	"%lld ms | Goal reached! %d meals\n"
# define HELP	"Input not valid!\n"
# define THERR	"Error creating threads."
# define MEMERR	"Error allocating memory."
# define RED	"\033[31m"

# include <stdbool.h>
# include <stddef.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <signal.h>

enum e_status {
	thinking = 0,
	sleeping = 1,
	waiting = 2,
	lonely = 3
};

typedef struct s_data
{
	int				numb;
	long long		starting_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				six_c;
	long long		ph_ttd;
	int				ph_n_meal;
	bool			ph_end;
	bool			ph_dead;
	int				ph_done;
	int				flag_done;
	int				n_thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philos
{
	pthread_t		*thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				last_meal;
	int				status;
	t_data			*data;
}					t_philos;

int			main(int argc, char **argv);
void		create_philos(t_philos *philos);
void		init(t_philos *philos, int argc, char **argv);
int			ft_atoi2(t_philos *philos, char *str);
void		cleaning(t_philos *philos, int flag);
void		free_mem(t_philos *philos);
long long	get_time(void);
void		sleep_ms(long long ms);
void		*routine(void *param);
void		output(t_philos *philos, int flg);
void		allocation(t_philos *philos);
void 		take_one_fork(t_philos *philos);
void		take_forks(t_philos *philos);
void		die(t_philos *philos);

#endif