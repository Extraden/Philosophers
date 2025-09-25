/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:06:06 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/24 23:29:51 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_sleep(long ms, t_data *data)
{
	long	start;
	int		stop;

	start = get_current_time();
	while (get_current_time() - start < ms)
	{
		pthread_mutex_lock(&data->stop_mutex);
		stop = data->stop;
		pthread_mutex_unlock(&data->stop_mutex);
		if (stop)
			break ;
		usleep(250);
	}
}

long	get_last_meal_time(t_philo *philo)
{
	long	t;

	pthread_mutex_lock(&philo->meal_mutex);
	t = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (t);
}

void	set_last_meal_time(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->meal_mutex);
}
