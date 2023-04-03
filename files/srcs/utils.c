/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:59:14 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/20 11:59:14 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	table_free(t_data *data)
{
	t_philo	*tmp;

	ft_goto_philo(&data, 1);
	while (data->philo->id != data->nb_philo)
	{
		tmp = data->philo;
		data->philo = data->philo->next;
		free(tmp);
	}
	free(data->philo);
	free(data);
}

void	table_print(t_data *data)
{
	ft_goto_philo(&data, 1);
	while (data->philo->id != data->nb_philo)
	{
		printf("%d %d found\n", ft_timecode(data), data->philo->id);
		data->philo = data->philo->next;
	}
	if (data->philo->id == data->nb_philo)
		printf("%d %d found\n", ft_timecode(data), data->philo->id);
}

void ft_goto_philo(t_data **data, int id)
{
	if (id == 0)
		ft_goto_philo(data, (*data)->nb_philo);
	else
	{
		if ((*data)->philo->id == id)
			return ;
		while ((*data)->philo->id != id)
			(*data)->philo = (*data)->philo->next;
	}
}

void	ft_wait(t_data *data, int id, int time)
{
	//long double	diff;
	t_time	time_start;
	//t_time	time_now;

	gettimeofday(&time_start, NULL);
	philo_is_dead(data, id);
/*	while (1)
	{
		gettimeofday(&time_now, NULL);
		diff = (time_now.tv_sec * 1000 + time_now.tv_usec / 1000) - (time_start.tv_sec * 1000 + time_start.tv_usec / 1000);
		if (diff >= time)
			break ;
	} */
	usleep(time);
	//philo_is_dead(data, id);
}

int	ft_timecode(t_data *data)
{
	long double	diff;

	gettimeofday(&data->time, NULL);
	diff = (data->time.tv_sec * 1000 + data->time.tv_usec / 1000) - (data->time_start.tv_sec * 1000 + data->time_start.tv_usec / 1000);
	return ((int) diff);
}
