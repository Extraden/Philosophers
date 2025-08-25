/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:02:59 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 17:03:39 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
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

t_philo *philo_init(int num_of_philos)
{
  t_philo *philos = malloc(sizeof(t_philo) * num_of_philos);
  if (!philos)
  {
    printf("Malloc error\n");
    return (NULL);
  }
  int i = 0;
  while (i < num_of_philos)
  {
    philos[i].id = i + 1;
    i++;
  }
  return (philos);
}

