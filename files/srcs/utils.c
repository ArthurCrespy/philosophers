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

void go_to_philo(t_data **data, int id)
{
	if (id == 0)
		go_to_philo(data, (*data)->nb_philo);
	else
	{
		if ((*data)->philo->id == id)
			return ;
		while ((*data)->philo->id != id)
			(*data)->philo = (*data)->philo->next;
	}
}

void	free_table(t_data *data)
{
	t_philo	*tmp;

	go_to_philo(&data, 1);
	while (data->philo->id != data->nb_philo)
	{
		tmp = data->philo;
		data->philo = data->philo->next;
		free(tmp);
	}
	free(data->philo);
	free(data);
}

void	print_table(t_data *data)
{
	go_to_philo(&data, 1);
	while (data->philo->id != data->nb_philo)
	{
		printf("%d %d found\n", ft_timecode(data), data->philo->id);
		data->philo = data->philo->next;
	}
	if (data->philo->id == data->nb_philo)
		printf("%d %d found\n", ft_timecode(data), data->philo->id);
}

int	ft_timecode(t_data *data)
{
	long double	diff;

	gettimeofday(&data->time, NULL);
	usleep(10000);
	diff = (((data->time.tv_sec + data->time.tv_usec) - (data->time_start.tv_sec + data->time_start.tv_usec)));
	return (diff);
}
