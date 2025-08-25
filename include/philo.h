/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:33:01 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 17:31:01 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>


typedef struct s_data t_data;

typedef struct s_philo
{
  int id;
  pthread_t thread;
  t_data  *table;
} t_philo ;

typedef	struct s_data
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;	
	int	time_to_sleep;
	int	times_to_eat;
  long start_time;
  t_philo *philos;
  pthread_mutex_t *forks;
}	t_data;

int	ft_atoi(char *arg);
int	check_args(char **av);
void	data_init(t_data *data, char **argv);
t_philo *philo_init(t_data *data);
long  get_current_time(void);
