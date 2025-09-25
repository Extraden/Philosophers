/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_of_philos)
	{
		set_last_meal_time(&d->philos[i], get_current_time());
		if (pthread_create(&d->philos[i].thread, 0, philo_routine,
				&d->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	join_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_of_philos)
	{
		if (pthread_join(d->philos[i].thread, 0) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	destroy_mutexes(t_data *d)
{
	int	i;

	if (pthread_mutex_destroy(&d->print_mutex) != 0)
		return (1);
	if (pthread_mutex_destroy(&d->stop_mutex) != 0)
		return (1);
	if (pthread_mutex_destroy(&d->full_count_mutex) != 0)
		return (1);
	i = 0;
	while (i < d->num_of_philos)
	{
		if (pthread_mutex_destroy(&d->forks[i].fork_mutex) != 0)
			return (1);
		if (pthread_mutex_destroy(&d->philos[i].meal_mutex) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	end_simulation(t_data *d)
{
	if (join_threads(d) != 0)
		return (1);
	if (destroy_mutexes(d) != 0)
		return (1);
	return (0);
}
