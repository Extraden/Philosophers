/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:33:01 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/08 18:33:33 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef struct s_data t_data;

typedef struct s_philo
{
  int id;
  pthread_t thread;
  pthread_mutex_t *min_fork;
  pthread_mutex_t *max_fork;
  long last_meal_time;
  t_data  *data;
} t_philo ;

typedef	struct s_data
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meals;
  long start_time;
  int stop;
  t_philo *philos;
  pthread_mutex_t *forks;
  pthread_mutex_t print_mutex;
  pthread_mutex_t stop_mutex;
}	t_data;

int	ft_atoi(char *arg);
int	check_args(char **av);
int  init(t_data *data, char *argv[]);
long  get_current_time(void);
int  start_simulation(t_data *data);
int  end_simulation(t_data *data);
void  my_sleep(long ms);
