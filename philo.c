/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:53 by dsemenov          #+#    #+#             */
/*   Updated: 2025/07/19 01:13:30 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int	main(int argc, char *argv[])
{
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
	printf("Hello");
	return (0);
}
