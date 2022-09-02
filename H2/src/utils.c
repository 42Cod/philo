/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:22:34 by hngo              #+#    #+#             */
/*   Updated: 2022/03/10 19:02:23 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	errormsg(char *str, int i)
{
	pthread_mutex_lock(&data()->print);
	printf("ERROR!: [%d] %s\n", i, str);
	data()->printable = false;
	pthread_mutex_unlock(&data()->print);
}

void	printmsg(int id, char *str)
{
	pthread_mutex_lock(&data()->print);
	if (data()->printable)
	{
		if (id == -1)
			printf("%lu\t%s\n", (get_time() - data()->starttime), str);
		else
			printf("%lu\t%d %s\n", (get_time() - data()->starttime), id, str);
	}
	pthread_mutex_unlock(&data()->print);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	neg;

	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	neg = 1;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
			res = res * 10 + *str - 48;
		else
			break ;
		str++;
	}
	return (res * neg);
}
