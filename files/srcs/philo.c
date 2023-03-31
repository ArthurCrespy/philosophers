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

int	philo_take_fork(t_data *data, int id)
{
	ft_goto_philo(&data, id);
	if (data->philo->fork == 0)
	{
		ft_goto_philo(&data, id - 1);
		if (data->philo->fork == 0)
		{
			data->philo->fork = 1;
			printf("%d %d has taken a fork\n", ft_timecode(data), id);
			ft_goto_philo(&data, id);
			data->philo->fork = 1;
			printf("%d %d has taken a fork\n", ft_timecode(data), id);
			return (1);
		}
	}
	return (0);
}

int	philo_drop_fork(t_data *data, int id)
{
	pthread_mutex_lock(&data->data_access);
	ft_goto_philo(&data, id);
	data->philo->fork = 0;
	ft_goto_philo(&data, id - 1);
	data->philo->fork = 0;
	pthread_mutex_unlock(&data->data_access);
	return (0);
}

int	philo_is_dead(t_data *data, int id)
{
	pthread_mutex_lock(&data->data_access);
	ft_goto_philo(&data, id);
	if (data->philo->eat_last + data->time_to_die < ft_timecode(data))
	{
		printf("%d %d died\n", ft_timecode(data), id);
		pthread_mutex_unlock(&data->data_access);
		exit(1);
	}
	pthread_mutex_unlock(&data->data_access);
	return (0);
}

void	philo_think(t_data *data, int id, int ttt)
{
	philo_is_dead(data, id);
	printf("%d %d is thinking\n", ft_timecode(data), data->philo->id);
	ft_wait(data, id, ttt * 1000);
	philo_sleep(data, id);
}

void	philo_sleep(t_data *data, int id)
{
	philo_is_dead(data, id);
	printf("%d %d is sleeping\n", ft_timecode(data), id);
	ft_wait(data, id, data->time_to_sleep * 1000);
	philo_eat(data, id);
}

void	philo_eat(t_data *data, int id)
{
	philo_is_dead(data, id);
	pthread_mutex_lock(&data->data_access);
	ft_goto_philo(&data, id);
	if (philo_take_fork(data, id))
	{
		data->philo->eat_last = ft_timecode(data);
		data->philo->eat_count++;
		printf("%d %d is eating\n", data->philo->eat_last, id);
		pthread_mutex_unlock(&data->data_access);
		ft_wait(data, id, data->time_to_eat * 1000);
	}
	else
	{
		ft_goto_philo(&data, id);
		pthread_mutex_unlock(&data->data_access);
		philo_think(data, id, data->time_to_eat);
	}
	philo_drop_fork(data, id);
	philo_think(data, id, data->time_to_eat);
}

void	*philosopher(void *arg)
{
	int     id;
	t_data	*data;

	data = (t_data*)arg;
	id = (*data).id_tmp;
	while (data->all_alive == 0)
		data = (t_data*)arg;
	philo_eat(data, id);
	return (NULL);
}