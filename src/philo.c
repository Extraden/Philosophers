/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissemenov <denissemenov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:53 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/03 19:10:07 by denissemeno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc != 5) && (argc != 6))
	{
		printf("Wrong number of arguments\n");
		printf("Usage:\n");
		printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [maximum_meals]\n");
		return (0);
	}
	if (check_args(argv))
	{
		printf("Wrong arguments\n");
		printf("Usage:\n");
		printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [maximum_meals]\n");
		return (0);
	}
  if (init(&data, argv) == NULL)
  {
    printf("Malloc error\n");
    return (1);
  }
  start_simulation(&data);
  while (1)
  {
	pthread_mutex_lock((data.stop_mutex));
	if (data.stop == 1)
	{
		end_simulation(&data);
		pthread_mutex_unlock((data.stop_mutex));
		return (0);
	}
	pthread_mutex_unlock((data.stop_mutex));
  }
  end_simulation(&data);
	return (0);
}
