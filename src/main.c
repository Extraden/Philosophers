/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:53 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/24 23:51:46 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	print_usage(void)
{
	printf("Wrong arguments\n");
	printf("Usage:\n");
	printf("./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep [maximum_meals]\n");
}

static int	monitoring_loop(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (is_dead(&data->philos[i]))
			{
				death_routine(&data->philos[i]);
				return (0);
			}
			i++;
		}
		pthread_mutex_lock(&data->full_count_mutex);
		if (data->full_count == data->num_of_philos)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock((&data->stop_mutex));
			pthread_mutex_unlock(&data->full_count_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->full_count_mutex);
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->stop_mutex);
		usleep(600);
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (((argc != 5) && (argc != 6)) || check_args(argv))
	{
		print_usage();
		return (0);
	}
	if (init(&data, argc, argv))
	{
		printf("Initialization error\n");
		return (1);
	}
	if (start_simulation(&data))
	{
		printf("Error while starting the simulation\n");
		return (1);
	}
	if (monitoring_loop(&data) == 0)
	{
		if (end_simulation(&data))
		{
			free(data.philos);
			free(data.forks);
			printf("Program stopped with error\n");
			return (1);
		}
	}
	free(data.philos);
	free(data.forks);
	return (0);
}
