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
	ft_print_status(data, philo->id, "is sleeping", 1);
	ft_smart_sleep(data, data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	if (data->time_to_die - ((data->time_to_eat * 2) + data->time_to_sleep)
		<= 100)
		return ;
	ft_print_status(data, philo->id, "is thinking", 1);
	ft_smart_sleep(data, data->time_to_die - ((data->time_to_eat * 2)
			+ data->time_to_sleep));
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&philo->fork);
	ft_print_status(data, philo->id, "has taken a fork", 1);
	if (philo->data->philo_nb == 1)
	{
		ft_smart_sleep(data, data->time_to_die + 10);
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	pthread_mutex_lock(philo->fork_left);
	ft_print_status(data, philo->id, "has taken a fork", 1);
	ft_print_status(data, philo->id, "is eating", 1);
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
	int			i;
	t_data		*data;
	long long	time;

	data = (t_data *)arg;
	ft_wait_start(data);
	usleep(5000);
	while (ft_check_alive(data, 200))
	{
		i = 0;
		time = ft_timestamp();
		while (i != data->philo_nb)
		{
			pthread_mutex_lock(&data->philo[i].data_access);
			if (time - data->philo[i].eat_last >= data->time_to_die)
			{
				ft_set_dead(data, i);
				pthread_mutex_unlock(&data->philo[i].data_access);
				break ;
			}
			pthread_mutex_unlock(&data->philo[i].data_access);
			i++;
		}
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
	pthread_mutex_lock(&philo->data_access);
	philo->eat_last = ft_timestamp();
	pthread_mutex_unlock(&philo->data_access);
	if ((philo->data->philo_nb % 2) && (philo->id == 1))
	{
		ft_print_status(data, philo->id, "is thinking", 1);
		ft_smart_sleep(data, data->time_to_eat);
	}
	if (!(philo->id % 2) && ft_check_alive(data, 0))
		philo_sleep_think(philo);
	while (ft_check_alive(data, 0))
	{
		philo_eat(philo);
		philo_sleep_think(philo);
		if (philo->eat_nb == data->eat_nb)
			break ;
	}
	ft_set_dead(data, -1);
	return (NULL);
}
