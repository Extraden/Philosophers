/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:17:43 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/03 20:52:05 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread.h>

static void philo_eat(t_philo *philo)
{
  pthread_mutex_lock(philo->left_fork);
  pthread_mutex_lock(philo->data->print_mutex);
  printf("%3ld %3d has taken left fork\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);
  pthread_mutex_lock(philo->right_fork);
  pthread_mutex_lock(philo->data->print_mutex);
  printf("%3ld %3d has taken right fork\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);
  pthread_mutex_lock(philo->data->stop_mutex);
  if (philo->data->stop == 1)
  {
    pthread_mutex_unlock(philo->data->stop_mutex);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return ;
  }
  pthread_mutex_unlock(philo->data->stop_mutex);
  philo->last_meal_time = get_current_time();
  pthread_mutex_lock(philo->data->print_mutex);
  printf("%3ld %3d is eating\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);
  my_sleep(philo->data->time_to_eat);
  pthread_mutex_unlock(philo->left_fork);
  pthread_mutex_unlock(philo->right_fork);

}

static void philo_sleep(t_philo *philo)
{
  pthread_mutex_lock(philo->data->stop_mutex);
  if (philo->data->stop == 1)
  {
    pthread_mutex_unlock(philo->data->stop_mutex);
    return ;
  }
  pthread_mutex_unlock(philo->data->stop_mutex);
  pthread_mutex_lock(philo->data->print_mutex);
  printf("%3ld %3d is sleeping\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);
  my_sleep(philo->data->time_to_sleep);
}

static void philo_think(t_philo *philo)
{
  pthread_mutex_lock(philo->data->stop_mutex);
  if (philo->data->stop == 1)
  {
    pthread_mutex_unlock(philo->data->stop_mutex);
    return ;
  }
  pthread_mutex_lock(philo->data->print_mutex);
  printf("%3ld %3d is thinking\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);
}

static void death_routine(t_philo *philo)
{
    if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      pthread_mutex_lock((philo->data->stop_mutex));
      philo->data->stop = 1;
      pthread_mutex_unlock((philo->data->stop_mutex));
      pthread_mutex_lock(philo->data->print_mutex);
      printf("%3ld %3d died\n", get_current_time() - philo->last_meal_time, philo->id);
      pthread_mutex_unlock(philo->data->print_mutex);
    }
}

static void  *philo_routine(void *arg)
{
  t_philo *philo = (t_philo *)arg;

  int i = 0;
  while (i < philo->data->max_meals)
  {
    if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      death_routine(philo);
      break;
    }
    philo_eat(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      death_routine(philo);
      break;
    }
    philo_sleep(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      death_routine(philo);
      break;
    }
    philo_think(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      death_routine(philo);
       break;
    }
    i++;
  }
  return (NULL);
}

int  start_simulation(t_data *data)
{
  int i = 0;
  while (i < data->num_of_philos)
  {
    data->philos[i].last_meal_time = get_current_time();
    if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
      return (1);
    i++;
  }
  return (0);
}
static int  join_threads(t_data *data)
{
  int i = 0;
  while (i < data->num_of_philos)
  {
    pthread_join(data->philos[i].thread, NULL);
    i++;
  }
  return (0);
}
static int  destroy_mutexes(t_data *data)
{
  if (!pthread_mutex_destroy(data->print_mutex))
    return (1);
  if (!pthread_mutex_destroy(data->stop_mutex))
    return (1);
  int i = 0;
  while (i < data->num_of_philos)
  {
    if (pthread_mutex_destroy(&data->forks[i]))
      return (1);
    i++;
  }
  return (0);
}

int  end_simulation(t_data *data)
{
  if (join_threads(data))
    return (1);

  if (destroy_mutexes(data))
    return (1);
  return (0);
}
