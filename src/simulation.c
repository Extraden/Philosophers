/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:17:43 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 20:26:50 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread.h>

static void  *routine(void *arg)
{
  t_philo *philo = (t_philo *)arg;
  printf("Thread %d has started...\n", philo->id);
  return (NULL);
}

void  start_simulation(t_data *data)
{
  int i = 0;
  while (i < data->num_of_philos)
  {
    pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
    i++;
  }

  i = 0;
  while (i < data->num_of_philos)
  {
    printf("%d ", data->philos[i].id);
    i++;
  }
}

void  end_simulation(t_data *data)
{
  int i = 0;
  while (i < data->num_of_philos)
  {
    pthread_join(data->philos[i].thread, NULL);
    i++;
  }
}
