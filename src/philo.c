/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:53 by dsemenov          #+#    #+#             */
/*   Updated: 2025/07/19 03:54:31 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	ft_atoi(char *arg)
{
	int	res;

	res = 0;
	while (*arg)
	{
		res = (res * 10) + (*arg - '0'); 
		arg++;
	}
	return (res);
}

int	is_numeric(char *arg)
{
	while (*arg)
	{
		if ((*arg < '0') || (*arg > '9'))
		{
			printf("Non numeric argument\n");
			return (0);
		}
		arg++;
	}
	return (1);
}

int	parse_args(char **av)
{
	char **tmp;

	tmp = &av[1];
	while (*tmp)
	{
		if (!is_numeric(*tmp))
			return (1);
		tmp++;
	}
	return (0);	
}

void	data_init(t_data *data, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->number_of_eatings = ft_atoi(argv[5]);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc != 5) && (argc != 6))
	{
		printf("Wrong number of arguments");
		return (1);
	}
	if (parse_args(argv))
	{
		printf("Wrong arguments\n");
		return (1);
	}
	data_init(&data, argv);	
	printf("Hello");
	return (0);
}
