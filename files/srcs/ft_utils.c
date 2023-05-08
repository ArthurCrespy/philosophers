/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:20:10 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/24 14:43:15 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_set_dead(t_data *data, int id)
{
	if (id >= 0)
		ft_print_status(data, data->philo[id].id, "died");
	pthread_mutex_lock(&data->data_access);
	data->philo_alive = 0;
	pthread_mutex_unlock(&data->data_access);
}

int	ft_check_alive(t_data *data)
{
	pthread_mutex_lock(&data->data_access);
	if (!data->philo_alive)
	{
		pthread_mutex_unlock(&data->data_access);
		return (0);
	}
	pthread_mutex_unlock(&data->data_access);
	return (1);
}

void	ft_print_status(t_data *data, int id, char *status)
{
	long long	time;

	time = ft_timestamp();
	usleep(100);
	pthread_mutex_lock(&data->data_access);
	if (data->philo_alive)
		printf("%lld %d %s\n", time - data->time_start, id, status);
	pthread_mutex_unlock(&data->data_access);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result *= 10;
		result += (str[i++] - '0');
	}
	return (result * sign);
}
