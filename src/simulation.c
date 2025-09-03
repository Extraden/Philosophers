/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:17:43 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/03 20:47:00 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread.h>

static void philo_eat(t_philo *philo)
{
  pthread_mutex_lock(philo->left_fork);
  pthread_mutex_lock(philo->right_fork);
  if (philo->data->is_dead == 1)
  {
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
  }
  my_sleep(philo->data->time_to_eat);
  if (philo->data->is_dead == 1)
  {
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
  }
  philo->last_meal_time = get_current_time();
  pthread_mutex_lock(philo->data->print_mutex);
  printf("%ld %d is eating\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);
  pthread_mutex_unlock(philo->left_fork);
  pthread_mutex_unlock(philo->right_fork);

}

static void philo_sleep(t_philo *philo)
{
  my_sleep(philo->data->time_to_sleep);
  pthread_mutex_lock(philo->data->print_mutex);
  printf("%ld %d is sleeping\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(philo->data->print_mutex);
}

static void philo_think(t_philo *philo)
{
    pthread_mutex_lock(philo->data->print_mutex);
    printf("%ld %d is thinking\n", get_current_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(philo->data->print_mutex);
}

static void  *philo_routine(void *arg)
{
  t_philo *philo = (t_philo *)arg;

  if (philo->data->max_meals == -1)
  {
  while (1)
  {
    if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      philo->data->is_dead = 1;
      printf("DEAD");
      break;
    }
    philo_eat(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      philo->data->is_dead = 1;
      printf("DEAD");
      break;
    }
    philo_sleep(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      philo->data->is_dead = 1;
      printf("DEAD");
      break;
    }
    philo_think(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      philo->data->is_dead = 1;
      printf("DEAD");
      break;
    }
  }
}

  return (NULL);
}

int  start_simulation(t_data *data)
{
  int i = 0;
  while (i < data->num_of_philos)
  {
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
    if (pthread_join(data->philos[i].thread, NULL))
      return (1);
    i++;
  }
  return (0);
}
static int  destroy_mutexes(t_data *data)
{
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
