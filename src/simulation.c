/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:17:43 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/24 23:53:01 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread.h>

static int should_stop(t_philo *philo)
{
  pthread_mutex_lock(&philo->data->stop_mutex);
  if (philo->data->stop == 1)
  {
    pthread_mutex_unlock(&philo->data->stop_mutex);
    return (1);
  }
  pthread_mutex_unlock(&philo->data->stop_mutex);
  return (0);
}

int is_dead(t_philo *philo)
{
  long  last_meal_time;

  last_meal_time = get_last_meal_time(philo);
  return (get_current_time() - last_meal_time >= philo->data->time_to_die);
}

void death_routine(t_philo *philo)
{
  print_action(philo, DIE);
}

static void release_forks(t_philo *philo)
{
  pthread_mutex_unlock(philo->max_fork);
  pthread_mutex_unlock(philo->min_fork);
}

static int philo_eat(t_philo *philo)
{
  if (is_dead(philo))
  {
    death_routine(philo);
    return (1);
  }
  if (should_stop(philo))
    return (1);
  pthread_mutex_lock(philo->min_fork);
  if (should_stop(philo))
  {
    pthread_mutex_unlock(philo->min_fork);
    return (1);
  }
  print_action(philo, TAKE_FORK);
  pthread_mutex_lock(philo->max_fork);
  if (should_stop(philo))
  {
    release_forks(philo);
    return (1);
  }
  print_action(philo, TAKE_FORK);
  if (should_stop(philo))
  {
    release_forks(philo);
    return (1);
  }
  print_action(philo, EAT);
  set_last_meal_time(philo, get_current_time());
  my_sleep(philo->data->time_to_eat, philo->data);
  release_forks(philo);
  return (0);
}

static int philo_sleep(t_philo *philo)
{
  if (is_dead(philo))
  {
    death_routine(philo);
    return (1);
  }
  if (should_stop(philo))
    return (1);
  print_action(philo, SLEEP);
  my_sleep(philo->data->time_to_sleep, philo->data);
  return (0);
}

static int philo_think(t_philo *philo)
{
  if (is_dead(philo))
  {
    death_routine(philo);
    return (1);
  }
  if (should_stop(philo))
    return (1);
  print_action(philo, THINK);
  return (0);
}

static  int run_routine_once(t_philo *philo)
{
  if (should_stop(philo) || is_dead(philo))
    return (1);
  if (philo_eat(philo))
    return (1);
  if (should_stop(philo) || is_dead(philo))
    return (1);
  if (philo_sleep(philo))
    return (1);
  if (should_stop(philo) || is_dead(philo))
    return (1);
  if (philo_think(philo))
    return (1);
  if (should_stop(philo) || is_dead(philo))
    return (1);
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
    pthread_mutex_lock(&philo->data->full_count_mutex);
    philo->data->full_count++;
    pthread_mutex_unlock(&philo->data->full_count_mutex);
  }
  return (NULL);
}

int  start_simulation(t_data *data)
{
  int i = 0;
  
  while (i < data->num_of_philos)
  {
    set_last_meal_time(&data->philos[i], get_current_time());
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
  if (pthread_mutex_destroy(&data->print_mutex))
    return (1);
  if (pthread_mutex_destroy(&data->stop_mutex))
    return (1);
  if (pthread_mutex_destroy(&data->full_count_mutex))
    return (1);
  int i = 0;
  while (i < data->num_of_philos)
  {
    if (pthread_mutex_destroy(&data->forks[i]))
      return (1);
    if (pthread_mutex_destroy(&data->philos[i].meal_mutex))
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
