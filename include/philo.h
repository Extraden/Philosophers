/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:33:01 by dsemenov          #+#    #+#             */
/*   Updated: 2025/09/25 01:45:25 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef enum e_action
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIE
}						t_action;

typedef struct s_data	t_data;

typedef struct s_fork
{
	bool				is_fork_taken;
	pthread_mutex_t		fork_mutex;
}						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	t_fork				*min_fork;
	t_fork				*max_fork;
	long				last_meal_time;
	pthread_mutex_t		meal_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	int					full_count;
	long				start_time;
	int					stop;
	t_philo				*philos;
	t_fork				*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		full_count_mutex;
}						t_data;

/* utils / args */
int		ft_atoi(char *arg);
int		check_args(char **av);
void	print_action(t_philo *philo, t_action action);
int		should_stop(t_philo *philo); /* FIX: вынес проверку стопа в утилиту */

/* init */
int		init(t_data *data, int argc, char *argv[]);

/* time */
long	get_current_time(void);
void	my_sleep(long ms, t_data *data);
long	get_last_meal_time(t_philo *philo);
void	set_last_meal_time(t_philo *philo, long time);

/* monitor */
int		monitoring_loop(t_data *data);

/* actions / routine / lifecycle */
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

int		is_dead(t_philo *philo);
void	*philo_routine(void *arg);

int		start_simulation(t_data *data);
int		end_simulation(t_data *data);

#endif