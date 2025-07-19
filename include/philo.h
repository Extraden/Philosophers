/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:33:01 by dsemenov          #+#    #+#             */
/*   Updated: 2025/07/19 04:03:16 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;	
	int	time_to_sleep;
	int	number_of_eatings;
}	t_data;


int	ft_atoi(char *arg);
int	parse_args(char **av);
