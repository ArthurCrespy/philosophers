/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:20:10 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/14 17:42:48 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	ft_timestamp(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_wait_start(t_data *data)
{
	long long	start;

	start = data->time_start;
	while (ft_timestamp() < start)
		usleep(100);
}

void	ft_print_status(t_data *data, int id, char *status)
{
	long long	time;

	time = ft_timestamp();
	usleep(100);
	pthread_mutex_lock(&data->data_access);
	printf("%lld %d %s\n", time - data->time_start, id, status);
	pthread_mutex_unlock(&data->data_access);
}

void	ft_smart_sleep(t_data *data, long long time)
{
	long long	i;

	i = ft_timestamp();
	if (!data)
	{
		while (1)
		{
			if ((ft_timestamp()) - i >= time)
				break ;
			usleep(10);
		}
	}
	while (data->philo_alive)
	{
		if ((ft_timestamp()) - i >= time)
			break ;
		usleep(10);
	}
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
