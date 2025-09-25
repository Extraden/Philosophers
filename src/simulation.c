/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:17:43 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/25 01:46:09 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	release_forks(t_philo *philo)
{
	philo->max_fork->is_fork_taken = false;
	pthread_mutex_unlock(&philo->max_fork->fork_mutex);
	philo->min_fork->is_fork_taken = false;
	pthread_mutex_unlock(&philo->min_fork->fork_mutex);
}

void	philo_eat(t_philo *philo)
{
	if (should_stop(philo) || is_dead(philo))
	{
		print_action(philo, DIE);
		return ;
	}
	pthread_mutex_lock(&philo->min_fork->fork_mutex);
	philo->min_fork->is_fork_taken = true;
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->min_fork->fork_mutex);
		return ;
	}
	print_action(philo, TAKE_FORK);
	if (philo->min_fork == philo->max_fork)
	{
		while (!should_stop(philo) && !is_dead(philo))
			usleep(1000);
		philo->min_fork->is_fork_taken = false;
		pthread_mutex_unlock(&philo->min_fork->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->max_fork->fork_mutex);
	philo->max_fork->is_fork_taken = true;
	if (should_stop(philo))
	{
		release_forks(philo);
		return ;
	}
	print_action(philo, TAKE_FORK);
	set_last_meal_time(philo, get_current_time());
	print_action(philo, EAT);
	my_sleep(philo->data->time_to_eat, philo->data);
	release_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (should_stop(philo) || is_dead(philo))
	{
		print_action(philo, DIE);
		return ;
	}
	print_action(philo, SLEEP);
	my_sleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	if (should_stop(philo) || is_dead(philo))
	{
		print_action(philo, DIE);
		return ;
	}
	print_action(philo, THINK);
	if (philo->data->num_of_philos % 2 == 1)
		my_sleep(philo->data->time_to_eat, philo->data);
}
