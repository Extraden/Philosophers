/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:53 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 17:14:20 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include "philo.h"


t_data  *parse_args(t_data *data, char *argv[])
{
  data_init(data, argv);
  data->philos = philo_init(data->num_of_philos);
  if (!data->philos)
    return (NULL);
  return (data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc != 5) && (argc != 6))
	{
		printf("Wrong number of arguments");
		return (0);
	}
	if (check_args(argv))
	{
		printf("Wrong arguments\n");
		return (0);
	}
  if (parse_args(&data, argv) == NULL)
  {
    printf("Malloc error\n");
    return (1);
  }
  long curr_time = get_current_time();
  printf("%lu", curr_time);
	return (0);
}
