/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:03:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/05 12:56:27 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*int	philo_take_fork(t_data *data, int id)
{
	ft_goto_philo(&data, id);
	if (data->philo->fork_avail == 0)
	{
		ft_goto_philo(&data, id - 1);
		if (data->philo->fork_avail == 0)
		{
			data->philo->fork_avail = 1;
			printf("%d %d has taken a fork\n", ft_timecode(data), id);
			ft_goto_philo(&data, id);
			data->philo->fork_avail = 1;
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
	data->philo->fork_avail = 0;
	ft_goto_philo(&data, id - 1);
	data->philo->fork_avail = 0;
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
	ft_wait(data, id, ttt);
	philo_eat(data, id);
}

void	philo_sleep(t_data *data, int id)
{
	philo_is_dead(data, id);
	printf("%d %d is sleeping\n", ft_timecode(data), id);
	ft_wait(data, id, data->time_to_sleep * 1000);
	philo_think(data, id, data->time_to_eat);
}*/

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = (t_data*)philo->data;
	pthread_mutex_lock(&data->data_access);
	pthread_mutex_lock(&philo->fork);
	ft_print_status(data, philo->id, "has taken a fork");
	if (philo->id == 1)
		pthread_mutex_lock(&data->philo[data->philo_nb - 1].fork);
	else
		pthread_mutex_lock(&data->philo[philo->id - 1].fork);
	printf("%d philo_eat\n", philo->id);
	ft_print_status(data, philo->id, "has taken a fork");
	ft_print_status(data, philo->id, "is eating");
	philo->eat_last = ft_timestamp();
	pthread_mutex_unlock(&data->data_access);
	ft_smart_sleep(data, data->time_to_eat * 1000);
	pthread_mutex_lock(&data->data_access);
	pthread_mutex_unlock(&philo->fork);
	if (philo->id == 1)
		pthread_mutex_unlock(&data->philo[data->philo_nb - 1].fork);
	else
		pthread_mutex_unlock(&data->philo[philo->id - 1].fork);

}

void	*philosopher(void *arg)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo*)arg;
	data = (t_data*)philo->data;
	data->time_start = ft_timestamp();
	ft_print_status(data, philo->id, "is alive");
	if (philo->id % 2)
		ft_smart_sleep(data, data->time_to_eat * 100);
	while (data->philo_alive)
	{
		philo_eat(philo);
		if (data->eat_nb >= 0 && philo->eat_nb >= data->eat_nb) {
			break ;
		}
		ft_print_status(data, philo->id, "is born");
		ft_print_status(data, philo->id, "is sleeping");
		ft_smart_sleep(data, data->time_to_sleep * 1000);
		ft_print_status(data, philo->id, "is thinking");
	}
	return (NULL);
}