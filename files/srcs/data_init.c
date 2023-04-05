/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:59:14 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/05 12:59:14 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int data_init(t_data **data)
{
	int i;

	i = 0;
	(*data)->philo_alive = 1;
	(*data)->philo = malloc(sizeof(t_philo) * (*data)->philo_nb);
	if (!(*data)->philo)
		return (1);
	if (pthread_mutex_init(&(*data)->data_access, NULL))
		return (1);
	if (!(*data)->philo)
		return (1);
	while (i < (*data)->philo_nb)
	{
		//printf("i = %d, id = %d, philo_nb = %d, time_to_die = %d, time_to_eat = %d, time_to_sleep = %d, eat_nb = %d, philo_alive = %d\n", i, i + 1, (*data)->philo_nb, (*data)->time_to_die, (*data)->time_to_eat, (*data)->time_to_sleep, (*data)->eat_nb, (*data)->philo_alive);
		(*data)->philo[i].id = i + 1;
		(*data)->philo[i].eat_nb = 0;
		(*data)->philo[i].data = *data;
		if (pthread_mutex_init(&(*data)->philo[i].fork, NULL))
			return (1);
		if (pthread_create(&(*data)->philo[i].thread, NULL, &philosopher, &(*data)->philo[i]))
			return (1);
		usleep(10);
		i++;
	}
	return (0);
}