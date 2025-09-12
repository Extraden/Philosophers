/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:17:43 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/12 23:14:51 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread.h>

static void philo_eat(t_philo *philo)
{
  pthread_mutex_lock(philo->min_fork);
  print_action(philo, TAKE_FORK);
  pthread_mutex_lock(philo->max_fork);
  print_action(philo, TAKE_FORK);
  print_action(philo, EAT);
  philo->last_meal_time = get_current_time();
  my_sleep(philo->data->time_to_eat);
  pthread_mutex_unlock(philo->min_fork);
  pthread_mutex_unlock(philo->max_fork);
  philo->meals_eaten++;
}

static void philo_sleep(t_philo *philo)
{
  print_action(philo, SLEEP);
  my_sleep(philo->data->time_to_sleep);
}

static void philo_think(t_philo *philo)
{
  print_action(philo, THINK);
}

static void death_routine(t_philo *philo)
{
  print_action(philo, DIE);
}

static int is_dead(t_philo *philo)
{
  return (get_current_time() - philo->last_meal_time >= philo->data->time_to_die);
}

static  int run_routine_once(t_philo *philo)
{
    if (is_dead(philo))
    {
      death_routine(philo);
      return (1);
    }
	  pthread_mutex_lock((&philo->data->stop_mutex));
    if (philo->data->stop == 1)
    {
	    pthread_mutex_unlock((&philo->data->stop_mutex));
      return (1);
    }
	  pthread_mutex_unlock((&philo->data->stop_mutex));
    if (is_dead(philo))
    {
      death_routine(philo);
      return (1);
    }
    philo_eat(philo);
    if (is_dead(philo))
    {
      death_routine(philo);
      return (1);
    }
	  pthread_mutex_lock((&philo->data->stop_mutex));
    if (philo->data->stop == 1)
    {
	    pthread_mutex_unlock((&philo->data->stop_mutex));
      return (1);
    }
	  pthread_mutex_unlock((&philo->data->stop_mutex));
    philo_sleep(philo);
    if (is_dead(philo))
    {
      death_routine(philo);
      return (1);
    }
	  pthread_mutex_lock((&philo->data->stop_mutex));
    if (philo->data->stop == 1)
    {
	    pthread_mutex_unlock((&philo->data->stop_mutex));
      return (1);
    }
	  pthread_mutex_unlock((&philo->data->stop_mutex));
    philo_think(philo);
    if (is_dead(philo))
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
    philo->data->full_count++;
  }
	pthread_mutex_lock((&philo->data->stop_mutex));
  philo->data->stop = 1;;
	pthread_mutex_unlock((&philo->data->stop_mutex));
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
