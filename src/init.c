/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:02:59 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/12 23:14:16 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include "philo.h"

static int check_args_range(t_data *data, int argc)
{
  if (data->num_of_philos == 0 || data->num_of_philos > 200)
  {
    printf("Wrong philos range\n");
    return (1);
  }
  if (data->time_to_die == 0)
  {
    printf("Wrong time_to_die range\n");
    return (1);
  }
  if (data->time_to_eat == 0)
  {
    printf("Wrong time_to_eat range\n");
    return (1);
  }
  if (data->time_to_sleep == 0)
  {
    printf("Wrong time_to_sleep range\n");
    return (1);
  }
  if (argc == 6 && data->max_meals == 0)
  {
    printf("Wrong max_meals range\n");
    return (1);
  }
  return (0);
}

static int	data_init(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
  {
    data->max_meals = ft_atoi(argv[5]);
  } else
  {
    data->max_meals = -1;
  }
  data->stop = 0;
  data->full_count = 0;
  data->start_time = get_current_time();
  return (0);
}

static int philos_init(t_data *data)
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
    philos[i].meals_eaten = 0;
    if (i < data->num_of_philos - 1)
    {
      philos[i].min_fork = &(data->forks[i]);
      philos[i].max_fork = &(data->forks[i + 1]);
    }
    else {
      philos[i].max_fork = &(data->forks[i]);
      philos[i].min_fork = &(data->forks[0]);
    }
    i++;
  }
  data->philos = philos;
  return (0);
}

static pthread_mutex_t  *forks_init(t_data *data)
{
  pthread_mutex_t *forks;
  forks = malloc(sizeof(*forks) * data->num_of_philos);
  if (!forks)
  {
    printf("Malloc error\n");
    return (NULL);
  }
  int i = 0;
  while (i < data->num_of_philos)
  {
    if (pthread_mutex_init(&forks[i], NULL))
    {
      free(forks);
      forks = NULL;
      return (NULL);
    }
    i++;
  }
  return (forks);
}

static int  mutexes_init(t_data *data)
{
  data->forks = forks_init(data);
  if (!data->forks)
    return (1);
  if (pthread_mutex_init(&data->print_mutex, NULL))
    return (1);
  if (pthread_mutex_init(&data->stop_mutex, NULL))
    return (1);
  if (pthread_mutex_init(&data->full_count_mutex, NULL))
    return (1);
  return (0);
}

int  init(t_data *data, int argc, char *argv[])
{
  if (data_init(data, argv))
    return (1);
  if (check_args_range(data, argc))
    return (1);
  if (mutexes_init(data))
    return (1);
  if (philos_init(data))
    return (1);
  return (0);
}
