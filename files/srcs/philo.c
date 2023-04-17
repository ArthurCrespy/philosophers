/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:03:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/14 17:41:13 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void    philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	ft_print_status(data, philo->id, "is sleeping");
	ft_smart_sleep(data, data->time_to_sleep);
}

void    philo_think(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	ft_print_status(data, philo->id, "is thinking");
	ft_smart_sleep(data, data->time_to_eat);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	usleep(10);
	ft_print_status(data, philo->id, "has taken a fork");
	ft_print_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->fork_left);
	ft_print_status(data, philo->id, "is eating");
	philo->eat_last = ft_timestamp();
	philo->eat_nb++;
	ft_smart_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->fork_left);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	ft_wait_start(data);
	if (philo->id % 2)
	{
		philo_sleep(philo);
		philo_think(philo);
	}
	while (data->philo_alive)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
