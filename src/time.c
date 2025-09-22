/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:06:06 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 17:19:51 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

long  get_current_time(void)
{
  struct timeval tv;
  long  time;

  gettimeofday(&tv, NULL);
  time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  return (time);
}

void  my_sleep(long ms, t_data *data)
{
  long  start;
  int   stop;

  start = get_current_time();
  while (get_current_time() - start < ms)
  {
    pthread_mutex_lock(&data->stop_mutex);
    stop = data->stop;
    pthread_mutex_unlock(&data->stop_mutex);
    if (stop)
      break ;
    usleep(250);
  }
}
