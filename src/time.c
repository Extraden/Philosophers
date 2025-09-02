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

long  get_current_time(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  long time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  return (time);
}

void  my_sleep(long ms)
{
  long start = get_current_time();
  while (get_current_time() - start < ms)
    usleep(250);
}
