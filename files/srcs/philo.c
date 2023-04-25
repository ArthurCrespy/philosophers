/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:03:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/24 14:46:00 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	ft_print_status(data, philo->id, "is sleeping");
	ft_smart_sleep(data, data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	if (data->time_to_eat - data->time_to_sleep <= 0)
		return ;
	ft_print_status(data, philo->id, "is thinking");
	ft_smart_sleep(data, data->time_to_eat - data->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&philo->fork);
	ft_print_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->fork_left);
	ft_print_status(data, philo->id, "has taken a fork");
	ft_print_status(data, philo->id, "is eating");
	pthread_mutex_lock(&data->data_access);
	philo->eat_last = ft_timestamp();
	philo->eat_nb++;
	pthread_mutex_unlock(&data->data_access);
	ft_smart_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_left);
}

void	*philo_checker(void *arg)
{
	int         i;
	t_data		*data;
	long long	time;

	i = 0;
	data = (t_data *)arg;
	ft_wait_start(data);
	while (data->philo_alive)
	{
		time = ft_timestamp();
		pthread_mutex_lock(&data->data_access);
		while (i != data->philo_nb && (*data).philo[i].eat_nb != 0)
		{
			if (time - data->philo[i].eat_last >= data->time_to_die)
			{
				pthread_mutex_unlock(&data->data_access);
				ft_print_status(data, data->philo[i].id, "died");
				pthread_mutex_lock(&data->data_access);
				data->philo_alive = 0;
				break ;
			}
			i++;
		}
		pthread_mutex_unlock(&data->data_access);
		if (i == data->philo_nb)
			i = 0;
		usleep(1000);
	}
	return (NULL);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	ft_wait_start(data);
	philo->eat_last = ft_timestamp();
	if (philo->id % 2 == 0)
	{
		philo_sleep(philo);
		philo_think(philo);
	}
	while (data->philo_alive)
	{
		philo_eat(philo);
		if (philo->eat_nb == data->eat_nb)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
