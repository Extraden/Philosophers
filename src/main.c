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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	print_usage(void)
{
	printf("Wrong arguments\n");
	printf("Usage:\n");
	printf("./philo number_of_philosophers time_to_die ");
	printf("time_to_eat time_to_sleep [maximum_meals]\n");
}

static int	monitor_check_death(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_of_philos)
	{
		if (is_dead(&d->philos[i]))
		{
			print_action(&d->philos[i], DIE);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitoring_loop(t_data *data)
{
	int	done;

	while (1)
	{
		if (data->max_meals != -1)
		{
			pthread_mutex_lock(&data->full_count_mutex);
			done = (data->full_count == data->num_of_philos);
			pthread_mutex_unlock(&data->full_count_mutex);
			if (done)
			{
				pthread_mutex_lock(&data->stop_mutex);
				data->stop = 1;
				pthread_mutex_unlock(&data->stop_mutex);
				return (0);
			}
		}
		if (monitor_check_death(data))
			return (0);
		pthread_mutex_lock(&data->stop_mutex);
		done = data->stop;
		pthread_mutex_unlock(&data->stop_mutex);
		if (done)
			return (0);
		usleep(250);
	}
}

static int	run_simulation(t_data *data)
{
	if (start_simulation(data) != 0)
	{
		printf("Error while starting the simulation\n");
		return (1);
	}
	(void)monitoring_loop(data);
	if (end_simulation(data) != 0)
	{
		free(data->philos);
		free(data->forks);
		printf("Program stopped with error\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (((argc != 5) && (argc != 6)) || check_args(argv))
	{
		print_usage();
		return (0);
	}
	if (init(&data, argc, argv) != 0)
	{
		printf("Initialization error\n");
		return (1);
	}
	if (run_simulation(&data) != 0)
		return (1);
	free(data.philos);
	free(data.forks);
	return (0);
}
