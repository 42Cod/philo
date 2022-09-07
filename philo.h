/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:28:13 by nmichael          #+#    #+#             */
/*   Updated: 2022/09/02 13:18:15 by nmichael         ###   ########.fr       */
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

typedef struct s_philos
{
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				last_meal;
	int				status;
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
	int				ph_n_meal;
	bool			ph_end;
	bool			ph_dead;
	int				ph_done;
	int				flag_done;
	int				n_thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks; // einmal fuur alle allocaten adann l und r auf diese pointen lassen 
	t_philos		*philos;
}					t_data;

int			main(int argc, char **argv);
void		create_philos(t_data
 *data);
void		init(t_data *data, int argc, char **argv);
int			ft_atoi2(t_data *data, char *str);
void		free_mem(t_data *data);
long long	get_time(void);
void		sleep_ms(long long ms);
void		*routine(void *param);
void		output(t_data *data, int flg);
void		allocation(t_data *data);
void 		take_one_fork(t_data *data);
void		take_forks(t_data *data);
void		die(t_data *data);
void		cleaning(t_data *data, int flag);
void		check_philos_death(t_data *data);
void		checker(t_data *data);


#endif