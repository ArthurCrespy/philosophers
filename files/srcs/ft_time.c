/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:04:25 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/08 16:04:25 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	ft_timestamp(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_wait_start(t_data *data)
{
	long long	start;

	start = data->time_start;
	while (ft_timestamp() < start)
		usleep(100);
}

void	ft_smart_sleep(t_data *data, long long time)
{
	long long	i;

	i = ft_timestamp();
	if (!data)
	{
		while (1)
		{
			if ((ft_timestamp()) - i >= time)
				break ;
			usleep(10);
		}
	}
	while (1)
	{
		if ((ft_timestamp()) - i >= time)
			break ;
		pthread_mutex_lock(&data->data_access);
		if (!data->philo_alive)
		{
			pthread_mutex_unlock(&data->data_access);
			return ;
		}
		pthread_mutex_unlock(&data->data_access);
		usleep(10);
	}
}
