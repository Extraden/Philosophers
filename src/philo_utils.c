/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 03:59:49 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/24 23:33:50 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

int	ft_atoi(char *arg)
{
	int	res;

	res = 0;
	while (*arg)
	{
		res = (res * 10) + (*arg - '0'); 
		arg++;
	}
	return (res);
}

static int	is_numeric(char *arg)
{
	while (*arg)
	{
		if ((*arg < '0') || (*arg > '9'))
		{
			printf("Non numeric argument\n");
			return (0);
		}
		arg++;
	}
	return (1);
}

int	check_args(char **av)
{
	char **tmp;

	tmp = &av[1];
	while (*tmp)
	{
		if (!is_numeric(*tmp))
			return (1);
		tmp++;
	}
	return (0);	
}

void	print_action(t_philo *philo, t_action action)
{
	if (action != DIE)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d ", get_current_time() - philo->data->start_time, philo->id);
	if (action == EAT)
  		printf("is eating\n");
	else if (action == SLEEP)
  		printf("is sleeping\n");
	else if (action == THINK)
  		printf("is thinking\n");
	else if (action == TAKE_FORK)
  		printf("has taken a fork\n");
	else if (action == DIE)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop == 0)
			philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
  		printf("died\n");
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
