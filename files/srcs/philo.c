/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:03:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/23 14:21:12 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int     dead(t_data *data, int id)
{
	int ttt;

	ttt = 0;
	pthread_mutex_lock(&data->data_access);
	go_to_philo(&data, id);
	if (data->philo->eat_last + data->time_to_die < ft_timecode(data))
	{
		printf("%d %d died\n", ft_timecode(data), id);
		pthread_mutex_unlock(&data->data_access);
		exit(1);
	}
	pthread_mutex_unlock(&data->data_access);
	return (0);
}

void    think(t_data *data, int id, int ttt)
{
	dead(data, id);
	if (ttt <= data->time_to_die + data->time_to_eat)
	{
		printf("%d %d is thinking\n", ft_timecode(data), data->philo->id);
		usleep(ttt * 1000);
	}
	else
		eat(data, id);
	sleeep(data, id);
}

void    sleeep(t_data *data, int id)
{
	dead(data, id);
	printf("%d %d is sleeping\n", ft_timecode(data), id);
	usleep(data->time_to_sleep * 1000);
	eat(data, id);
}

void eat(t_data *data, int id)
{
	int ttt;

	ttt = 0;
	dead(data, id);
	pthread_mutex_lock(&data->data_access);
	go_to_philo(&data, id);
	id = data->philo->id;
	if (data->philo->fork == 0)
	{
		go_to_philo(&data, id - 1);
		if (data->philo->fork == 0)
		{
			data->philo->fork = 1;
			printf("%d %d has taken a fork\n", ft_timecode(data), id);
			go_to_philo(&data, id);
			data->philo->fork = 1;
			printf("%d %d has taken a fork\n", ft_timecode(data), id);
			data->philo->eat_last = ft_timecode(data);
			data->philo->eat_count++;
			printf("%d %d is eating\n", data->philo->eat_last, id);
			pthread_mutex_unlock(&data->data_access);
			usleep(data->time_to_eat * 1000);
		}
		else
		{
			go_to_philo(&data, id);
			ttt = data->time_to_eat;
			pthread_mutex_unlock(&data->data_access);
			think(data, id, ttt);
		}
	}
	else
	{
		go_to_philo(&data, id);
		pthread_mutex_unlock(&data->data_access);
		think(data, id, data->time_to_eat);
	}
	pthread_mutex_lock(&data->data_access);
	data->philo->fork = 0;
	go_to_philo(&data, id - 1);
	data->philo->fork = 0;
	go_to_philo(&data, id);
	pthread_mutex_unlock(&data->data_access);
	think(data, id, data->time_to_eat * 2);
}

void	*philosopher(void *arg)
{
	int     id;
	t_data	*data;

	data = (t_data*)arg;
	id = (*data).id_tmp;
	while (data->all_alive == 0)
		data = (t_data*)arg;
	eat(data, id);
	return (NULL);
}