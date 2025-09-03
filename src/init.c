/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:02:59 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/03 16:59:24 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "philo.h"

void	data_init(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
    data->max_meals = ft_atoi(argv[5]);
  else
    data->max_meals = -1;
  data->is_dead = 0;
  data->start_time = get_current_time();
}

t_philo *philos_init(t_data *data)
{
  t_philo *philos = malloc(sizeof(t_philo) * data->num_of_philos);
  if (!philos)
  {
    printf("Malloc error\n");
    return (NULL);
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
  return (philos);
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
  data->print_mutex = malloc(sizeof(pthread_mutex_t));
  if (!data->print_mutex)
    return (1);
  pthread_mutex_init(data->print_mutex, NULL);
  return (0);
}

t_data  *init(t_data *data, char *argv[])
{
  data_init(data, argv);
  if (mutexes_init(data))
    return (NULL);
  data->philos = philos_init(data);
  if (!data->philos)
    return (NULL);
  return (data);
}