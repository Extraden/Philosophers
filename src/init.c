/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:02:59 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/25 01:45:33 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int	parse_and_init(t_data *d, int argc, char **av)
{
	d->num_of_philos = ft_atoi(av[1]);
	d->time_to_die = ft_atoi(av[2]);
	d->time_to_eat = ft_atoi(av[3]);
	d->time_to_sleep = ft_atoi(av[4]);
	if (argc == 6)
		d->max_meals = ft_atoi(av[5]);
	else
		d->max_meals = -1;
	d->stop = 0;
	d->full_count = 0;
	d->start_time = get_current_time();
	if (d->num_of_philos == 0 || d->num_of_philos > 200)
	{
		printf("Wrong philos range\n");
		return (1);
	}
	if (d->time_to_die == 0 || d->time_to_eat == 0 || d->time_to_sleep == 0)
	{
		printf("Wrong time range\n");
		return (1);
	}
	if (argc == 6 && d->max_meals == 0)
	{
		printf("Wrong max_meals range\n");
		return (1);
	}
	return (0);
}

static t_fork	*forks_init(t_data *d)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(*forks) * d->num_of_philos);
	if (!forks)
	{
		printf("Malloc error\n");
		return (NULL);
	}
	i = 0;
	while (i < d->num_of_philos)
	{
		forks[i].is_fork_taken = false;
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL) != 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static int	mutexes_init(t_data *d)
{
	if (!d->forks)
		return (1);
	if (pthread_mutex_init(&d->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&d->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&d->full_count_mutex, NULL) != 0)
		return (1);
	return (0);
}

static int	philos_init(t_data *d)
{
	int	i;

	d->philos = malloc(sizeof(*d->philos) * d->num_of_philos);
	if (!d->philos)
	{
		printf("Malloc error\n");
		return (1);
	}
	i = 0;
	while (i < d->num_of_philos)
	{
		d->philos[i].id = i + 1;
		d->philos[i].data = d;
		if (i < d->num_of_philos - 1)
			d->philos[i].min_fork = &d->forks[i];
		else
			d->philos[i].min_fork = &d->forks[0];
		if (i == d->num_of_philos - 1)
			d->philos[i].max_fork = &d->forks[i];
		else
			d->philos[i].max_fork = &d->forks[i + 1];
		if (pthread_mutex_init(&d->philos[i].meal_mutex, NULL) != 0)
		{
			free(d->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init(t_data *data, int argc, char *argv[])
{
	if (parse_and_init(data, argc, argv) != 0)
		return (1);
	data->forks = forks_init(data);
	if (mutexes_init(data) != 0)
		return (1);
	if (philos_init(data) != 0)
		return (1);
	return (0);
}
