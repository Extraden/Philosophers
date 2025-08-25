/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:06:06 by dsemenov          #+#    #+#             */
/*   Updated: 2025/08/25 17:12:52 by dsemenov         ###   ########.fr       */
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


