/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:02:59 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 20:18:48 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "philo.h"

void	data_init(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
    data->times_to_eat = ft_atoi(argv[5]);

}

t_philo *philo_init(t_data *data)
{
  data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
  if (!data->philos)
  {
    printf("Malloc error\n");
    return (NULL);
  }
  int i = 0;
  while (i < data->num_of_philos)
  {
    data->philos[i].id = i;
    i++;
  }
  return (data->philos);
}

