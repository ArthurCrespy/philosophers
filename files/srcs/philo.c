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
	pthread_mutex_lock(&philo->data_access);
	philo->eat_last = ft_timestamp();
	philo->eat_nb++;
	pthread_mutex_unlock(&philo->data_access);
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
	usleep(1);
	while (data->philo_alive)
	{
		time = ft_timestamp();
		while (i != data->philo_nb)
		{
			pthread_mutex_lock(&data->philo[i].data_access);
			if (time - data->philo[i].eat_last >= data->time_to_die)
			{
				ft_print_status(data, data->philo[i].id, "died");
				data->philo_alive = 0;
				break ;
			}
			pthread_mutex_unlock(&data->philo[i].data_access);
			i++;
		}
		if (i == data->philo_nb)
			i = 0;
		usleep(100);
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
	if (!(philo->id % 2))
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
