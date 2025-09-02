/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:33:01 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 20:42:12 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef struct s_data t_data;

typedef struct s_philo
{
  int id;
  pthread_t thread;
  pthread_mutex_t *left_fork;
  pthread_mutex_t *right_fork;
  t_data  *table;
} t_philo ;

typedef	struct s_data
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;	
	int	time_to_sleep;
	int	max_meals;
  long start_time;
  int is_dead;
  t_philo *philos;
  pthread_mutex_t *forks;
}	t_data;

int	ft_atoi(char *arg);
int	check_args(char **av);
t_data  *init(t_data *data, char *argv[]);
void	data_init(t_data *data, char **argv);
t_philo *philos_init(t_data *data);
long  get_current_time(void);
void  start_simulation(t_data *data);
void  end_simulation(t_data *data);
