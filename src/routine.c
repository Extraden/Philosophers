/* ************************************************************************** */
/*                                                                             */
/*   routine.c                                          :+:      :+:    :+:   */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	long	last;

	last = get_last_meal_time(philo);
	return (get_current_time() - last >= philo->data->time_to_die);
}

static void	stagger_start(t_philo *p)
{
	if (p->data->num_of_philos % 2 == 0)
	{
		if (p->id % 2 == 0)
			my_sleep(p->data->time_to_eat / 2, p->data);
	}
	else if (p->id % 2 == 0)
		my_sleep(p->data->time_to_eat, p->data);
}

static int	run_once(t_philo *p)
{
	if (should_stop(p) || is_dead(p))
		return (1);
	philo_eat(p);
	if (should_stop(p) || is_dead(p))
		return (1);
	philo_sleep(p);
	if (should_stop(p) || is_dead(p))
		return (1);
	philo_think(p);
	return (should_stop(p) || is_dead(p));
}

void	*philo_routine(void *arg)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)arg;
	stagger_start(p);
	if (p->data->max_meals == -1)
	{
		while (!should_stop(p))
			if (run_once(p))
				break ;
	}
	else
	{
		i = 0;
		while (i < p->data->max_meals && !should_stop(p))
		{
			if (run_once(p))
				break ;
			i++;
		}
		pthread_mutex_lock(&p->data->full_count_mutex);
		p->data->full_count++;
		pthread_mutex_unlock(&p->data->full_count_mutex);
	}
	return (0);
}
