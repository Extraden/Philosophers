/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:53 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 16:01:00 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include "philo.h"

t_philo *philo_init(int num_of_philos)
{
  t_philo *philos = malloc(sizeof(t_philo) * num_of_philos);
  if (!philos)
  {
    printf("Malloc error\n");
    return (NULL);
  }
  int i = 0;
  while (i < num_of_philos)
  {
    philos[i].id = i + 1;
    i++;
  }
  return (philos);
}

void	data_init(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
    data->times_to_eat = ft_atoi(argv[5]);

  data->philos = philo_init(data->num_of_philos);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc != 5) && (argc != 6))
	{
		printf("Wrong number of arguments");
		return (0);
	}
	if (check_args(argv))
	{
		printf("Wrong arguments\n");
		return (0);
	}
	data_init(&data, argv);	
  int i = 0;
  while (i < data.num_of_philos)
  {
    printf("Philo id: %d\n", data.philos[i].id);
    i++;
  }
	return (0);
}
