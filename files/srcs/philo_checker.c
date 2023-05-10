/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:59:13 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/10 14:59:13 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_checker(void *arg)
{
	int			i;
	t_data		*data;
	long long	time;

	data = (t_data *)arg;
	ft_wait_start(data);
	usleep(5000);
	while (ft_check_alive(data, 10))
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
