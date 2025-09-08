/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:02:59 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/08 18:15:19 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "philo.h"

int	data_init(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
  if (data->num_of_philos == 0)
    return (1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
    data->max_meals = ft_atoi(argv[5]);
  else
    data->max_meals = -1;
  data->stop = 0;
  data->start_time = get_current_time();
  return (0);
}

int philos_init(t_data *data)
{
  t_philo *philos = malloc(sizeof(t_philo) * data->num_of_philos);
  if (!philos)
  {
    printf("Malloc error\n");
    return (1);
  }
  int i = 0;
  while (i < data->num_of_philos)
  {
    philos[i].id = i + 1;
    philos[i].data = data;
    philos[i].left_fork = &(data->forks[i]);
    philos[i].right_fork = &(data->forks[(i + 1) % data->num_of_philos]);
    i++;
  }
  data->philos = philos;
  return (0);
}

pthread_mutex_t  *forks_init(t_data *data)
{
  pthread_mutex_t *forks;
  forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
  if (!forks)
  {
    printf("Malloc error\n");
    return (NULL);
  }
  int i = 0;
  while (i < data->num_of_philos)
  {
    pthread_mutex_init(&forks[i], NULL); // Error check (all mutex init and destroy)
    i++;
  }
  return (forks);
}

int  mutexes_init(t_data *data)
{
  data->forks = forks_init(data);
  if (!data->forks)
    return (1);
  if (pthread_mutex_init(&data->print_mutex, NULL))
    return (1);
  if (pthread_mutex_init(&data->stop_mutex, NULL))
    return (1);
  return (0);
}

t_data  *init(t_data *data, char *argv[])
{
  if (data_init(data, argv))
    return (NULL);
  if (mutexes_init(data))
    return (NULL);
  if (philos_init(data))
    return (NULL);
  return (data);
}
