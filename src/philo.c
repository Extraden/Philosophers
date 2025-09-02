/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:53 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 20:51:00 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include "philo.h"

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
  if (init(&data, argv) == NULL)
  {
    printf("Malloc error\n");
    return (1);
  }
  long curr_time = get_current_time();
  start_simulation(&data);
  end_simulation(&data);
  printf("Time of end of simulation: %lu", curr_time);
	return (0);
}
