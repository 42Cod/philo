/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:28:13 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/09 13:14:04 by nmichael         ###   ########.fr       */
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
	lonely = 3,
	ate = 4
};

typedef struct s_philos //thread erstellen und durchloopen und heccken ob die
{
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	long long		last_meal;
	int				status;
	struct s_data	*data;
	int				ph_n_meal;
}					t_philos;

typedef struct s_data
{
	int				numb;
	long long		starting_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				six_c;
	long long		ph_ttd;
	bool			ph_end;
	bool			ph_dead;
	int				ph_done;
	int				flag_done;
	int				n_thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philos		*philos;
}					t_data;

int			main(int argc, char **argv);
void		create_philos(t_data *data);
void		init(t_data *data, int argc, char **argv);
int			ft_atoi2(t_data *data, char *str);
void		free_mem(t_data *data);
long long	get_time(void);
void		sleep_ms(long long ms);
void		*routine(void *param);
void		output(t_philos *philos, int flg);
void		allocation(t_data *data);
void		take_one_fork(t_data *data);
void		take_forks(t_data *data);
void		die(t_data *data);
void		cleaning(t_data *data, int flag);
void		eat(t_philos *philos);
void		sleepi(t_philos *philos);
void		think(t_philos *philos);
void		checker(t_philos *philos);
void		*routine1(void *param);
void		sleep_ms2(long long ms, t_philos *philos);
void		checker2(t_data *data);

#endif