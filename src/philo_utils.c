/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 03:59:49 by dsemenov          #+#    #+#             */
/*   Updated: 2025/07/19 04:00:35 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
