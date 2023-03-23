/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:03:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/22 17:03:54 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void    think(t_data *data)
{
	if (data->philo->eat_last + data->time_to_sleep + data->time_to_eat < ft_timecode(data) - 10)
	{
		printf("%d %d is thinking\n", ft_timecode(data), data->philo->id);
		while (data->philo->eat_last + data->time_to_sleep + data->time_to_eat < ft_timecode(data) - 10)
			;
	}
	else
		eat(data);
	sleeep(data);
}

void    sleeep(t_data *data)
{
	printf("%d %d is sleeping\n", ft_timecode(data), data->philo->id);
	usleep(data->time_to_sleep * 1000);
	think(data);
}

void eat(t_data *data)
{
	int id;

	id = data->philo->id;
	pthread_mutex_lock(&data->data_access);
	if (data->philo->fork == 0)
	{
		go_to_philo(&data, data->philo->id - 1);
		if (data->philo->fork == 0)
		{
			data->philo->fork = 1;
			printf("%d %d has taken a fork\n", ft_timecode(data), data->philo->id + 1);
			go_to_philo(&data, id);
			data->philo->fork = 1;
			printf("%d %d has taken a fork\n", ft_timecode(data), data->philo->id);
			data->philo->eat_last = ft_timecode(data);
			data->philo->eat_count++;
			printf("%d %d is eating\n", data->philo->eat_last, data->philo->id);
			pthread_mutex_unlock(&data->data_access);
			usleep(data->time_to_eat * 1000);
		}
		else
		{
			go_to_philo(&data, id);
			pthread_mutex_unlock(&data->data_access);
			think(data);
		}
	}
	else
	{
		go_to_philo(&data, id);
		pthread_mutex_unlock(&data->data_access);
		think(data);
	}
	pthread_mutex_lock(&data->data_access);
	data->philo->fork = 0;
	go_to_philo(&data, data->philo->id - 1);
	data->philo->fork = 0;
	go_to_philo(&data, id);
	pthread_mutex_unlock(&data->data_access);
	sleeep(data);
}

void	*philosopher(void *arg)
{
	t_data	*data;

	data = (t_data*)arg;
	while (data->all_alive == 0)
		data = (t_data*)arg;
	eat(data);
	return (NULL);
}
