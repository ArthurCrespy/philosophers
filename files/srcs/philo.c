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
	printf("%d %d is thinking\n", ft_timecode(data), data->philo->id);
}

void    sleeep(t_data *data)
{
	printf("%d %d is sleeping\n", ft_timecode(data), data->philo->id);
	usleep(data->time_to_sleep * 1000);
}

void eat(t_data *data)
{
	int id;

	id = data->philo->id;
	pthread_mutex_lock(&data->philo->fork);
	printf("%d %d has taken a fork\n", ft_timecode(data), data->philo->id);
	go_to_philo(&data, data->philo->id - 1);
	pthread_mutex_lock(&data->philo->fork);
	printf("%d %d has taken a fork\n", ft_timecode(data), data->philo->id);
	go_to_philo(&data, id);
	data->philo->last_eat = ft_timecode(data);
	printf("%d %d is eating\n", data->philo->last_eat, data->philo->id);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->philo->fork);
	go_to_philo(&data, data->philo->id - 1);
	pthread_mutex_unlock(&data->philo->fork);
}

void	*philosopher(void *arg)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data*)arg;
	eat(data);
	think(data);
	sleeep(data);
	return (NULL);
}
