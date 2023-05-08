/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:59:14 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/24 14:40:39 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	data_thread_init(t_data **data)
{
	int	i;

	i = 1;
	(*data)->philo_alive = 1;
	(*data)->time_start = ft_timestamp() + ((*data)->philo_nb * 100);
	while (i < (*data)->philo_nb && i % 2)
	{
		if (pthread_create(&(*data)->philo[i].thread, NULL, &philosopher,
				&(*data)->philo[i]))
			return (1);
		i += 2;
	}
	i = 0;
	while (i < (*data)->philo_nb && !(i % 2))
	{
		if (pthread_create(&(*data)->philo[i].thread, NULL, &philosopher,
				&(*data)->philo[i]))
			return (1);
		i += 2;
	}
	if (pthread_create(&(*data)->philo_checker, NULL, &philo_checker,
			(*data)))
		return (1);
	return (0);
}

int	data_init_fork(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philo_nb)
	{
		(*data)->philo[i].fork_left = &(*data)->philo[(*data)->philo[i].id_left]
			.fork;
		i++;
	}
	return (0);
}

int	data_init(t_data **data)
{
	int		i;

	i = 0;
	(*data)->philo = malloc(sizeof(t_philo) * (*data)->philo_nb);
	if (!(*data)->philo)
		return (1);
	if (pthread_mutex_init(&(*data)->data_access, NULL))
		return (1);
	while (i < (*data)->philo_nb)
	{
		(*data)->philo[i].id = i + 1;
		(*data)->philo[i].eat_nb = 0;
		(*data)->philo[i].data = *data;
		if (i == 0)
			(*data)->philo[i].id_left = (*data)->philo_nb - 1;
		else
			(*data)->philo[i].id_left = i - 1;
		if (pthread_mutex_init(&(*data)->philo[i].fork, NULL)
			|| pthread_mutex_init(&(*data)->philo[i].data_access, NULL))
			return (1);
		i++;
	}
	data_init_fork(data);
	data_thread_init(data);
	return (0);
}

int	data_destroy(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philo_nb)
	{
		if (pthread_join((*data)->philo[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join((*data)->philo_checker, NULL))
		return (1);
	i = 0;
	while (i < (*data)->philo_nb)
	{
		if (pthread_mutex_destroy(&(*data)->philo[i].fork))
		i++;
	}
	if (pthread_mutex_destroy(&(*data)->data_access))
		return (1);
	free((*data)->philo);
	free(*data);
	return (0);
}
