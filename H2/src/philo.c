/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:34:22 by hngo              #+#    #+#             */
/*   Updated: 2022/03/10 19:02:35 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_data(void)
{
	int	i;

	i = -1;
	while (++i < data()->threads_num)
	{
		if (pthread_mutex_destroy(&data()->philos[i]->lock_fork) != 0)
			errormsg("Couldn't destroy Mutex", i);
	}
	if (pthread_mutex_destroy(&data()->print) != 0)
		errormsg("Couldn't destroy Mutex", i);
	if (pthread_mutex_destroy(&data()->init_lock) != 0)
		errormsg("Couldn't destroy Mutex", i);
	i = -1;
	while (++i < data()->threads_num)
	{
		free(data()->philos[i]);
		data()->philos[i] = NULL;
	}
	free(data()->philos);
	data()->philos = NULL;
}

bool	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '0')
			return (false);
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	main(int argc, char **argv)
{
	if (check_input(argv) && (argc == 5 || argc == 6))
		init_data(argv);
	else
		printf("Input not valid!\n");
	if (data()->philos)
		free_data();
	return (0);
}
