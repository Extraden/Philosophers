/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissemenov <denissemenov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:17:43 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/03 18:06:34 by denissemeno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread.h>

static void philo_eat(t_philo *philo)
{
  pthread_mutex_lock(philo->left_fork);
  pthread_mutex_lock(philo->right_fork);
  my_sleep(philo->data->time_to_eat);
  philo->last_meal_time = get_current_time();
  pthread_mutex_lock(philo->data->print_mutex);
  printf("Philo %d is eating...\n", philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);
  pthread_mutex_unlock(philo->left_fork);
  pthread_mutex_unlock(philo->right_fork);

}

static void philo_sleep(t_philo *philo)
{
  my_sleep(philo->data->time_to_eat);
  pthread_mutex_lock(philo->data->print_mutex);
  printf("Philo %d is sleeping...\n", philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);

}

static void philo_think(t_philo *philo)
{
    pthread_mutex_lock(philo->data->print_mutex);
    printf("Philo %d is thinking...\n", philo->id);
    pthread_mutex_unlock(philo->data->print_mutex);
}

static void  *philo_routine(void *arg)
{
  t_philo *philo = (t_philo *)arg;

  philo_eat(philo);
  philo_sleep(philo);
  philo_think(philo);

  return (NULL);
}

void  start_simulation(t_data *data)
{
  int i = 0;
  while (i < data->num_of_philos)
  {
    pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
    i++;
  }
}
static void  join_threads(t_data *data)
{
  int i = 0;
  while (i < data->num_of_philos)
  {
    pthread_join(data->philos[i].thread, NULL);
    i++;
  }
}
static void  destroy_mutexes(t_data *data)
{
  int i = 0;
  while (i < data->num_of_philos)
  {
    pthread_mutex_destroy(&data->forks[i]);
    i++;
  }
}

void  end_simulation(t_data *data)
{
  join_threads(data);
  destroy_mutexes(data);
}
