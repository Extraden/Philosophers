/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:53 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/08 20:52:12 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"
#include <stdlib.h>

static int monitoring_loop(t_data *data)
{
  while (1)
  {
	usleep(250);
	pthread_mutex_lock((&data->stop_mutex));
	if (data->stop == 1)
	{
		pthread_mutex_unlock((&data->stop_mutex));
		end_simulation(data);
		return (0);
	}
	pthread_mutex_unlock((&data->stop_mutex));
  }
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (((argc != 5) && (argc != 6)) || check_args(argv))
	{
		printf("Wrong arguments\n");
		printf("Usage:\n");
		printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [maximum_meals]\n");
		return (0);
	}
	if (init(&data, argv))
	{
		printf("Initialization error\n");
		return (1);
 	}
 	start_simulation(&data);
	monitoring_loop(&data);
  	end_simulation(&data);
	free(data.philos);
	free(data.forks);
	return (0);
}
