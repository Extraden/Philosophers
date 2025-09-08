/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:17:43 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/08 20:50:25 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

static void philo_eat(t_philo *philo)
{
  pthread_mutex_lock(philo->min_fork);
  pthread_mutex_lock(&philo->data->print_mutex);
  printf("%ld %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(&philo->data->print_mutex);
  pthread_mutex_lock(philo->max_fork);
  pthread_mutex_lock(&philo->data->print_mutex);
  printf("%ld %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(&philo->data->print_mutex);
  philo->last_meal_time = get_current_time();
  pthread_mutex_lock(&philo->data->print_mutex);
  printf("%ld %d is eating\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(&philo->data->print_mutex);
  my_sleep(philo->data->time_to_eat);
  pthread_mutex_unlock(philo->min_fork);
  pthread_mutex_unlock(philo->max_fork);
}

static void philo_sleep(t_philo *philo)
{
  pthread_mutex_lock(&philo->data->print_mutex);
  printf("%ld %d is sleeping\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(&philo->data->print_mutex);
  my_sleep(philo->data->time_to_sleep);
}

static void philo_think(t_philo *philo)
{
  pthread_mutex_lock(&philo->data->print_mutex);
  printf("%ld %d is thinking\n", get_current_time() - philo->data->start_time, philo->id);
  pthread_mutex_unlock(&philo->data->print_mutex);
}

static void death_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d died\n", get_current_time() - philo->last_meal_time, philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

static  int run_routine_once(t_philo *philo)
{
    if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      death_routine(philo);
      return (1);
    }
    if (philo->data->stop == 1)
      return (1);
    philo_eat(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      death_routine(philo);
      return (1);
    }
    if (philo->data->stop == 1)
      return (1);
    philo_sleep(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      death_routine(philo);
      return (1);
    }
    if (philo->data->stop == 1)
      return (1);
    philo_think(philo);
      if (get_current_time() - philo->last_meal_time >= philo->data->time_to_die)
    {
      death_routine(philo);
      return (1);
    }
    return (0);
}

static void  *philo_routine(void *arg)
{
  t_philo *philo = (t_philo *)arg;

  if (philo->data->max_meals == -1)
  {
    while (1)
    {
      if (run_routine_once(philo))
        break ;
    }
  }
  else
  {
    int i = 0;
    while (i < philo->data->max_meals)
    {
      if (run_routine_once(philo))
        break ;
      i++;
    }
  }
  philo->data->stop = 1;;
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
  if (!pthread_mutex_destroy(&data->print_mutex))
    return (1);
  if (!pthread_mutex_destroy(&data->stop_mutex))
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
  // TODO: Free mallocs
  return (0);
}
